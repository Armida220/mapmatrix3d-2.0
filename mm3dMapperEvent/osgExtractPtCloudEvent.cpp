// osgExtractPtCloudEvent.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "osgExtractPtCloudEvent.h"
#include "ThreadSafeUpdateCallback.h"
#include "InterfaceBaseDrawer.h"
#include "InterfaceOsgFinder.h"
#include "InterfaceOsgExtractWall.h"
#define PTCOLOR osg::Vec4d(0, 0, 1, 1)																   //����ɫ
																					   //��Ƭ�Ƕ�ƫ����ֵ

void COsgExtractPtCloudEvent::UpdateActivatedStatus(std::vector<OperatingState> vecOpState)
{
	bool flag = false;

	if (isActivated == true)
	{
		flag = true;
	}

	isActivated = isActivate(vecOpState, OPS_EXTRCT_PT_CLOUD);

	if (isActivated == false && flag == true)													 //������
	{

		osg::ref_ptr<CThreadSafeUpdateCallback> spChildCallback = dynamic_cast<CThreadSafeUpdateCallback*>(mRoot->getUpdateCallback());
		if (spChildCallback != NULL)
		{
			int num = tempGroup->getNumChildren();
			osg::ref_ptr<osg::Node> childNode;
			for (int i = 0; i < num; i++)
			{
				childNode = tempGroup->getChild(i);
				spChildCallback->RemoveChild(tempGroup, childNode);
			}
		}
		iSigEventCallBack->EmitSigShowOpsHint("");
	}

	if (isActivated && flag == false)																//�ռ���
	{
		vecTotalTriangle.clear();
		InterfaceOsgExtractWallFactory IWallFactory;
		InterfaceOsgExtractWall* IWall = IWallFactory.create();
		IWall->clearPointDataInSqlite3(iSqliteDatabase, "Points");
		vecCorlor.clear();
		vecNormal.clear();
		iSigEventCallBack->EmitSigShowOpsHint("��ȡ���ƣ���Ctrl + ��������ȡ����");
	}
}


bool COsgExtractPtCloudEvent::handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa)
{
	if (isActivated)
	{
		InterfaceOsgExtractWallFactory IWallFactory;
		InterfaceOsgExtractWall* IWall = IWallFactory.create();
		if (IsLeftClick(ea) && GetKeyState(VK_CONTROL) < 0)
		{
			CPickResult pickResult = PickResult(ea.getX(), ea.getY(), mViewer);
			osg::Vec3d worldPt = pickResult.worldPt;
			osg::Vec3d normal = pickResult.worldNm;
			osg::NodePath np = pickResult.nodePath;
			osg::Matrix worldMatrix = pickResult.matrix;
			if (worldPt.x() == 0 && worldPt.y() == 0 && worldPt.z() == 0)
			{
				return false;
			}
			
			iSigEventCallBack->EmitSigShowOpsHint("��ȡ���ƣ�������ȡ...");
			std::vector<osg::Vec3d> vecTriangle;
			//�Զ�����
			InterfaceOsgExtractWallFactory IWallFactory;
			InterfaceOsgExtractWall* IWall = IWallFactory.create();
			vecNormal.push_back(normal);
			if (!IWall->DrawTriangleEx(mRoot, np, worldPt, worldMatrix, vecTriangle, vecNormal,vecCorlor, ANGLE, similarity))
			{
				iSigEventCallBack->EmitSigShowOpsHint("��ȡ���ƣ���ȡʧ�ܣ�������");
				return false;
			}

			//��ȡ�ɹ������Ƶ�
			if (vecTriangle.size() > 0)
			{
				vecTotalTriangle.push_back(vecTriangle);
				std::vector<std::vector<osg::Vec3d> > vecTriangleTemp;
				vecTriangleTemp.push_back(vecTriangle);
				IWall->savePointDataToSqlite3(vecTriangleTemp, iSqliteDatabase, "Points", true);//׷�ӱ���
																								 			
				osg::ref_ptr<osg::Group> outlineGroup = new osg::Group;
				InterfaceBaseDrawerFactory IDrawerFactory;
				InterfaceBaseDrawer* IDrawer = IDrawerFactory.create();
				for (int i = 0; i < vecTriangle.size(); ++i)
				{
					IDrawer->BaseDrawPtOperate(vecTriangle[i], PTCOLOR, 3.5, outlineGroup, worldMatrix);
				}
				osg::ref_ptr<CThreadSafeUpdateCallback> spChildCallback = dynamic_cast<CThreadSafeUpdateCallback*>(mRoot->getUpdateCallback());
				if (spChildCallback != NULL)
				{
					spChildCallback->AddChild(tempGroup, outlineGroup);
				}
				iSigEventCallBack->EmitSigShowOpsHint("��ȡ���ƣ���BackSpace������ȡ�㣬��Ctrl + ������������ȡ");
			}
		}
		else if (IsKeyPress(ea))
		{
			if (ea.getKey() == osgGA::GUIEventAdapter::KEY_BackSpace)					 //BackSpace
			{
				if (tempGroup->getNumChildren() > 0)
				{
					tempGroup->removeChild(tempGroup->getNumChildren() - 1);
					vecTotalTriangle.pop_back();
					IWall->savePointDataToSqlite3(vecTotalTriangle, iSqliteDatabase, "Points");//ˢ�±���
					if (!vecCorlor.empty())
					{
						vecCorlor.pop_back();
					}
					if (!vecNormal.empty())
					{
						vecNormal.pop_back();
					}	
				}
				return false;
			}
			else if (ea.getKey() == osgGA::GUIEventAdapter::KEY_Z)
			{
				ClearGroupResult(tempGroup);
				vecTotalTriangle.clear();
				IWall->clearPointDataInSqlite3(iSqliteDatabase, "Points");//������ݿ�
				vecCorlor.clear();
				vecNormal.clear();
				return false;
			}
		}
	}


	return false;
}



