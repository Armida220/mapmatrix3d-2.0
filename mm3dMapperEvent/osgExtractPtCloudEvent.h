#pragma once
#include "BaseUserEvent.h"
#include "OSG_Plus.h"
#include "InterfaceUserEventCallBack.h"
#include "InterfaceSqliteDatabase.h"
#include <vector>

class COsgExtractPtCloudEvent : public CBaseUserEvent
{
public:
	COsgExtractPtCloudEvent(osgViewer::Viewer *viewer, osg::Group *root, osg::ref_ptr<osg::Group> TempGroup, InterfaceSigEventCallBack* iSigEventCallBack) : CBaseUserEvent(viewer)
	{
		mViewer = viewer;
		mRoot = root;
		isActivated = false;
		this->iSigEventCallBack = iSigEventCallBack;
		tempGroup = TempGroup;
		//����database����Ӧ��table
		InterfaceSqliteDatabaseFactory iSqliteDatabaseFactory;
		iSqliteDatabase = iSqliteDatabaseFactory.create();
		ANGLE = 10;
		similarity = 0.9;
	}

	bool handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa);

	double ANGLE;
	double similarity;//��ɫ���ƶ�
protected:
	void UpdateActivatedStatus(std::vector<OperatingState> vecOpState);
	
	osgViewer::Viewer *mViewer;
	osg::Group *mRoot;
	osg::Group *tempGroup;																										//������ʱ��ͼ
	InterfaceSigEventCallBack* iSigEventCallBack;

	bool isActivated;																											//ǽ���¼�����

	std::vector<std::vector<osg::Vec3d> > vecTotalTriangle;																		//����������

	InterfaceSqliteDatabase* iSqliteDatabase;

	std::vector<osg::Vec3d> vecNormal;    //�����������������
	std::vector<osg::Vec4> vecCorlor;     //������������
};
