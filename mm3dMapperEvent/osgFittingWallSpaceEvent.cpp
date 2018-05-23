// osgFittingWallSpaceEvent.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "ThreadSafeUpdateCallback.h"
#include "InterfaceBaseDrawer.h"
#include "osgFittingWallSpaceEvent.h"
#include "InterfaceOsgFinder.h"

#include "Geometry.h"
#include "cvLine.h"

#define WALLCOLOR osg::Vec4d(0,1,1,0.4)      //ǽ����ɫ

void COsgFittingWallSpaceEvent::UpdateActivatedStatus(std::vector<OperatingState> vecOpState)
{
	bool flag = false;

	if (isActivated == true)
	{
		flag = true;
	}
	isActivated = isActivate(vecOpState, OPS_FITTING_WALLSPACE);

	if (isActivated == false && flag == true)
	{
		ClearGroupResult(tempGroup);
		iSigEventCallBack->EmitSigShowOpsHint("");
	}

	if (isActivated && flag == false)																//�ռ���
	{
		InterfaceOsgExtractWallFactory IWallFactory;
		InterfaceOsgExtractWall* IWall = IWallFactory.create();
		IWall->addDraggerToScene(mRoot, slotGroup, editWallGroup);
		//��ȡ������
		IWall->readWallDataFromSqlite3(planePara, iSqliteDatabase, "runData.db");
		
		InterfaceBaseDrawerFactory IDrawerFactory;
		InterfaceBaseDrawer* IDrawer = IDrawerFactory.create();
		
		
		ClearGroupResult(editWallGroup);
		IWall->getWorldMatrix(mRoot, worldMatrix);
		for (size_t i = 0; i < planePara.size(); ++i)
		{
			IDrawer->BaseDrawPolygon(planePara[i].coord, WALLCOLOR, editWallGroup, worldMatrix);
		}
		
		
		//��ȡ������
		IWall->readPointDataFromSqlite3(vecTotalTriangle,iSqliteDatabase,"Points");

		if (vecTotalTriangle.size()>0)
		{
			std::vector<osg::Vec3d> vecNormal;
			IWall->readPointDataFromSqlite3(vecNormal, iSqliteDatabase, "Normal");
			normal = vecNormal[0];
			if (IWall->fittingWallSpace(vecTotalTriangle, planePara, normal, worldMatrix))//���ƽ��
			{
				InterfaceBaseDrawerFactory IDrawerFactory;
				InterfaceBaseDrawer* IDrawer = IDrawerFactory.create();
				IDrawer->BaseDrawPolygon(planePara.back().coord, WALLCOLOR, editWallGroup, worldMatrix);

				vecTotalTriangle.clear();
				IWall->clearPointDataInSqlite3(iSqliteDatabase,"Points");
				char strMsg[299];
				sprintf(strMsg, "��ȡǽ�棺ǽ����б�ǣ�%f �� ǽ�������%lf", planePara.back().angle, planePara.back().err);
				iSigEventCallBack->EmitSigShowOpsHint(strMsg);
				IWall->saveWallDataToSqlite3(planePara, iSqliteDatabase, "runData.db");
			}
		}
		else
		{
			iSigEventCallBack->EmitSigShowOpsHint("��ȡǽ�棺�Ҳ���������Ϣ");
		}
	}
}

bool COsgFittingWallSpaceEvent::handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa)
{
	if (isActivated)
	{
		InterfaceBaseDrawerFactory IDrawerFactory;
		InterfaceBaseDrawer* IDrawer = IDrawerFactory.create();
		InterfaceOsgExtractWallFactory IWallFactory;
		InterfaceOsgExtractWall* IWall = IWallFactory.create();

		//ִ���϶�����¼�
		if (IWall->draggerEvent(atWall, ea, aa, mViewer, _activeDragger, editWallGroup, tempGroup, partnerPoint, wallSelected, _pointer, endPoint, planePara, worldMatrix, WALLCOLOR))
		{
			//����ǽ����Ϣ
			IWall->saveWallDataToSqlite3(planePara, iSqliteDatabase, "runData.db");
		}
		if (IsLeftClick(ea) && GetKeyState(VK_CONTROL) < 0)//�����¼�
		{
			CPickResult pickResult = PickResult(ea.getX(), ea.getY(), mViewer);
			worldPt = pickResult.worldPt;
			
			if (worldPt.x() == 0 && worldPt.y() == 0 && worldPt.z() == 0)
			{
				return false;
			}
			int _i = 0;
			for (std::vector<WallInfo>::iterator ite = (planePara).begin(); ite != (planePara).end(); ++ite)
			{
				if (CL::Point_In_Rectangle_3D(worldPt, partnerPoint, (*ite).coord))//����ǽ����
				{
					//����wall�ϼ�����¼�
					if (!pushEvent(ea, aa))
					{
						return false;
					}
					atWall = true;
					editWallGroup->removeChild(_i);
					IDrawer->BaseDrawPolygon((*ite).coord, WALLCOLOR, tempGroup, worldMatrix);
					wallSelected = *ite;
					(planePara).erase(ite);
					IWall->saveWallDataToSqlite3(planePara, iSqliteDatabase, "runData.db");
					return false;
				}
				++_i;
			}
			return false;
		}
		else if(IsKeyPress(ea))
		{ 
			if (ea.getKey() == osgGA::GUIEventAdapter::KEY_M)
			{
				char strMsg[99];
				sprintf(strMsg, "�ڵ���:%d", mRoot->getNumChildren());
				iSigEventCallBack->EmitSigShowOpsHint(strMsg);
			}
			else if (ea.getKey() == osgGA::GUIEventAdapter::KEY_BackSpace)
			{
				int num = editWallGroup->getNumChildren();
				if (num>0)
				{
					editWallGroup->removeChild(num - 1);
					planePara.pop_back();
					//����ǽ����Ϣ
					IWall->saveWallDataToSqlite3(planePara, iSqliteDatabase, "runData.db");
				}
			}
			else if (ea.getKey() == osgGA::GUIEventAdapter::KEY_Z)
			{
				ClearGroupResult(editWallGroup);
				ClearGroupResult(tempGroup);
				planePara.clear();
				//����ǽ����Ϣ
				IWall->saveWallDataToSqlite3(planePara, iSqliteDatabase, "runData.db");
			}
		}
		
	}
	return false;
}





bool COsgFittingWallSpaceEvent::pushEvent(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa)
{
	osgUtil::LineSegmentIntersector::Intersections intersections;
	_pointer.reset();
	if (mViewer->computeIntersections(ea.getX(), ea.getY(), intersections))
	{
		_pointer.setCamera(mViewer->getCamera());
		_pointer.setMousePosition(ea.getX(), ea.getY());
		for (osgUtil::LineSegmentIntersector::Intersections::iterator hitr = intersections.begin(); hitr != intersections.end(); ++hitr)
		{
			_pointer.addIntersection(hitr->nodePath, hitr->getWorldIntersectPoint());
		}
		for (osg::NodePath::iterator itr = _pointer._hitList.front().first.begin(); itr != _pointer._hitList.front().first.end(); ++itr)
		{
			CDraggerPoint* dragger = dynamic_cast<CDraggerPoint*>(*itr);
			if (dragger)
			{
				dragger->handle(_pointer, ea, aa);
				_activeDragger = dragger;
				return true;
			}
		}
	}
	return false;
}


