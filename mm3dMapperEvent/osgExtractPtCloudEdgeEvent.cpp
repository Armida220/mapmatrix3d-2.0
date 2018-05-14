// osgExtractPtCloudEdgeEvent.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "osgExtractPtCloudEdgeEvent.h"
#include "InterfaceOsgExtractWall.h"
#include "ThreadSafeUpdateCallback.h"
#include <osg/LOD>

void COsgExtractPtCloudEdgeEvent::UpdateActivatedStatus(std::vector<OperatingState> vecOpState)
{
	bool flag = false;

	if (isActivated == true)
	{
		flag = true;
	}
	isActivated = isActivate(vecOpState, OPS_EXTRCT_PT_CLOUD_EDGE);

	if (isActivated == false && flag == true)
	{
	
	}

	if (isActivated && flag == false)																//�ռ���
	{
		
	}

	if (isActivated)  //����
	{
		vecWorldCoord.clear();
		InterfaceOsgExtractWallFactory IWallFactory;
		InterfaceOsgExtractWall* IWall = IWallFactory.create();
		//��ȡ����
		
		IWall->readPointDataFromSqlite3(vecWorldCoord, iSqliteDatabase, "Points");
		if (vecWorldCoord.size() == 0)
		{
			iSigEventCallBack->EmitSigShowOpsHint("��ȡ���Ʊ�Ե���Ҳ���������Ϣ");
			return;
		}
		iSigEventCallBack->EmitSigShowOpsHint("��ȡ���Ʊ�Ե��������ȡ���Ʊ�Ե");
		
		IWall->getWorldMatrix(mRoot, worldMatrix);
		std::vector<osg::Vec3d> vecEdge;
		CAlphaShapes alphaShapes;
		alphaShapes.extractPtCloudEdge(vecWorldCoord,vecEdge,alpha);

		//����Ե
		ClearGroupResult(tempGroup);
		InterfaceBaseDrawerFactory IDrawerFactory;
		InterfaceBaseDrawer* IDrawer = IDrawerFactory.create();
		osg::ref_ptr<osg::Group> group = new osg::Group;
		osg::ref_ptr<osg::Group> group1 = new osg::Group;
		for (size_t i = 0; i < vecEdge.size()-1; i+=2)
		{
			IDrawer->BaseDrawLineOperate(vecEdge[i], vecEdge[i+1], osg::Vec4d(1, 0, 0, 1), 3.5, group, worldMatrix);
			IDrawer->BaseDrawPtOperate(vecEdge[i], osg::Vec4d(1, 0, 0, 1), 3.5, group1, worldMatrix);
		}
		osg::ref_ptr<osg::LOD> lod = new osg::LOD();
		lod->addChild(group, 0.0f, 300);
		lod->addChild(group1, 300, 10000);
		osg::ref_ptr<CThreadSafeUpdateCallback> spChildCallback = dynamic_cast<CThreadSafeUpdateCallback*>(mRoot->getUpdateCallback());
		if (spChildCallback != NULL)
		{
			spChildCallback->AddChild(mapperGroup, lod);
		}
		iSigEventCallBack->EmitSigShowOpsHint("��ȡ���Ʊ�Ե����Ե��ȡ��ɣ���Z���ɳ�����ȡ���");
	}
}

bool COsgExtractPtCloudEdgeEvent::handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa)
{
	if (isActivated)
	{
		if (IsKeyPress(ea))
		{
			if (ea.getKey() == osgGA::GUIEventAdapter::KEY_Z)//������ȡ���
			{
				if (tempGroup->getNumChildren() != 0)
				{
					return false;
				}
				int num = mapperGroup->getNumChildren();
				if (num > 0)
				{
					mapperGroup->removeChild(num - 1);
				}
				iSigEventCallBack->EmitSigShowOpsHint("��ȡ���Ʊ�Ե����ȡ����ѳ���");
				InterfaceBaseDrawerFactory IDrawerFactory;
				InterfaceBaseDrawer* IDrawer = IDrawerFactory.create();
				osg::ref_ptr<osg::Group> group = new osg::Group;
				for (size_t i = 0;i<vecWorldCoord.size();++i)
				{
					IDrawer->BaseDrawPtOperate(vecWorldCoord[i],osg::Vec4d(0,0,1,1), 3.5, group, worldMatrix);
				}
				osg::ref_ptr<CThreadSafeUpdateCallback> spChildCallback = dynamic_cast<CThreadSafeUpdateCallback*>(mRoot->getUpdateCallback());
				if (spChildCallback != NULL)
				{
					spChildCallback->AddChild(tempGroup, group);
				}
				return false;
			}
		}
	}
	return false;
}