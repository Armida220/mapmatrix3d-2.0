// osgDrawEdgeEvent.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "osgHandDrawEdgeEvent.h"
#include "InterfaceOsgExtractWall.h"
#include "ThreadSafeUpdateCallback.h"
void COsgHandDrawEdgeEvent::UpdateActivatedStatus(std::vector<OperatingState> vecOpState)
{
	bool flag = false;

	if (isActivated == true)
	{
		flag = true;
	}

	isActivated = isActivate(vecOpState, OPS_DRAW_EDGE_BY_HAND);

	if (isActivated == false && flag == true)
	{
		vecWorldCoord.clear();
		ISigEventCallBack->EmitSigShowOpsHint("");

		ClearGroupResult(tempGroup);
	}

	if (isActivated && flag == false)																//�ռ���
	{
		//��ȡ������
		InterfaceOsgExtractWallFactory IWallFactory;
		InterfaceOsgExtractWall* IWall = IWallFactory.create();
		IWall->readPointDataFromSqlite3(vecPoints, iSqliteDatabase, "Points");
		if (vecPoints.empty())
		{
			isActivated = false;
			ISigEventCallBack->EmitSigShowOpsHint("�Ҳ������ݣ�");
			return;
		}
		InterfaceBaseDrawerFactory IDrawFactory;
		InterfaceBaseDrawer* IDrawer = IDrawFactory.create();
		osg::ref_ptr<osg::Group> outlineGroup = new osg::Group;
		osg::Matrix worldMatrix;
		IWall->getWorldMatrix(mRoot, worldMatrix);

		for (size_t i = 0; i < vecPoints.size() - 1; i += 2)
		{
			IDrawer->BaseDrawPtOperate(vecPoints[i], osg::Vec4(0, 0, 1, 1), 3.5, outlineGroup, worldMatrix);
		}
		osg::ref_ptr<CThreadSafeUpdateCallback> spChildCallback = dynamic_cast<CThreadSafeUpdateCallback*>(mRoot->getUpdateCallback());
		if (spChildCallback != NULL)
		{
			spChildCallback->AddChild(dataGroup, outlineGroup);
		}
		
		isCatch = true;   //�رղ�׽
		ISigEventCallBack->EmitSigShowOpsHint("��Ctrl + ������ߣ�˫����������BackSpace���ˣ���ESC�˳��¼�     ��׽[X]������");
	}
}

bool COsgHandDrawEdgeEvent::handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa)
{
	if (isActivated)
	{
		if (IsLeftClick(ea) && GetKeyState(VK_CONTROL) < 0)
		{
			CPickResult pResult = PickResult(ea.getX(), ea.getY(), mViewer);
			osg::Vec3d worldPt = pResult.worldPt;
			osg::Matrix worldMatrix = pResult.matrix;

			if (worldPt.x() == 0 && worldPt.y() == 0 && worldPt.z() == 0)
			{
				return false;
			}
			if (isCatch)
			{
				if (!CatchPointOperate(worldPt, vecPoints))
				{
					return false;
				}
			}
			//������
			osg::Vec4d color(1.0, 0, 0.0, 1.0);
			double size = 5.5f;
			LeftClickExtractHandPaintLineOperate(vecWorldCoord, worldPt, color, size, mapperGroup, worldMatrix);					   //���û�����
			ISigEventCallBack->EmitSigShowOpsHint("��Ctrl + ������ߣ�˫����������BackSpace���ˣ���ESC�˳��¼�����X�л���׽״̬");
		}
		else if (IsMouseMove(ea) && GetKeyState(VK_CONTROL) < 0)
		{
			CPickResult pResult = PickResult(ea.getX(), ea.getY(), mViewer);
			osg::Vec3d worldPt = pResult.worldPt;
			osg::Matrix worldMatrix = pResult.matrix;

			if (worldPt.x() == 0 && worldPt.y() == 0 && worldPt.z() == 0)
			{
				return false;
			}

			//������
			osg::Vec4d color(1.0, 0, 0.0, 1.0);
			double size = 5.5f;
			MouseMoveExtractHandPaintLineOperate(vecWorldCoord, worldPt, color, size, tempGroup, worldMatrix);		//��������ƶ�����

		}
		else if (IsDoubleClick(ea) && GetKeyState(VK_CONTROL) < 0)
		{
			CPickResult pResult = PickResult(ea.getX(), ea.getY(), mViewer);
			osg::Vec3d worldPt = pResult.worldPt;

			if (worldPt.x() == 0 && worldPt.y() == 0 && worldPt.z() == 0)
			{
				return false;
			}

			DoubleClickDrawExtractHandPaintOperate(vecWorldCoord, tempGroup);
			ISigEventCallBack->EmitSigShowOpsHint("��C��������ƣ���Z��������Ƶı�Ե��");
		}
		else if (IsKeyPress(ea))
		{
			if (ea.getKey() == osgGA::GUIEventAdapter::KEY_BackSpace)
			{
				int childNum = mapperGroup->getNumChildren();

				if (childNum > 0)
				{
					mapperGroup->removeChild(childNum - 1);
				}

				vecWorldCoord.pop_back();
			}
			else if (ea.getKey() == osgGA::GUIEventAdapter::KEY_Z)					 //z
			{
				ClearGroupResult(mapperGroup);
				vecWorldCoord.clear();
			}
			else if (ea.getKey() == osgGA::GUIEventAdapter::KEY_C)					 //c
			{
				clearGroupSafety(mRoot,dataGroup);
				vecPoints.clear();
				ISigEventCallBack->EmitSigShowOpsHint("");
			}
			else if (ea.getKey() == osgGA::GUIEventAdapter::KEY_X)					 //x
			{
				if (isCatch == true)
				{
					isCatch = false;
					ISigEventCallBack->EmitSigShowOpsHint("�رղ�׽");
				}
				else
				{
					isCatch = true;
					ISigEventCallBack->EmitSigShowOpsHint("������׽");
				}
			}
		}
	}
	else
	{
		vecWorldCoord.clear();
	}

	return false;
}

bool COsgHandDrawEdgeEvent::CatchPointOperate(osg::Vec3d &worldPt, std::vector<osg::Vec3d>& vecPoints)
{
	bool flag = false;
	double dis = 99999,d = 0;
	osg::Vec3d pt(0,0,0);
	for (size_t i = 0;i<vecPoints.size();++i)
	{
		d = distancep2p(worldPt, vecPoints[i]);
		
		if (d<dis)
		{
			dis = d;
			pt = vecPoints[i];
			flag = true;
		}
	}
	worldPt = pt;
	return flag;
}


void COsgHandDrawEdgeEvent::clearGroupSafety(osg::Group* father, osg::Group* children)
{
	osg::ref_ptr<CThreadSafeUpdateCallback> spChildCallback = dynamic_cast<CThreadSafeUpdateCallback*>(father->getUpdateCallback());
	if (spChildCallback != NULL)
	{
		int num = children->getNumChildren();
		osg::ref_ptr<osg::Node> childNode;
		for (int i = 0; i < num; i++)
		{
			childNode = children->getChild(i);
			spChildCallback->RemoveChild(children, childNode);
		}
	}
}