#pragma once
#include "BaseUserEvent.h"
#include "operationState.h"
#include "InterfaceUserEventCallBack.h"
#include "InterfaceOsgFinder.h"
#include "InterfaceSqliteDatabase.h"
#include <vector>
#include "PGControl.h"

class COsgExtractWallInsectEvent : public CBaseUserEvent
{
public:
	COsgExtractWallInsectEvent(osgViewer::Viewer *viewer, osg::Group *root, osg::ref_ptr<osg::Group> EditWallGroup, osg::ref_ptr<osg::Group> MapperGroup,
		osg::ref_ptr<osg::Group> TempGroup, osg::ref_ptr<osg::Group> DataGroup,  InterfaceSigEventCallBack* iSigEventCallBack) : CBaseUserEvent(viewer)
	{
		mViewer = viewer;
		mRoot = root;
		isActivated = false;
		isEditPoint = false;
		this->iSigEventCallBack = iSigEventCallBack;

		tempGroup = TempGroup;
		editWallGroup = EditWallGroup;
		mapperGroup = MapperGroup;
		tempEditGroup = DataGroup;
		conn = nullptr;
		bRoofReady = false;

		InterfaceSqliteDatabaseFactory iSqliteDatabaseFactory;
		iSqliteDatabase = iSqliteDatabaseFactory.create();
	}
protected:
	void UpdateActivatedStatus(std::vector<OperatingState> vecOpState);
	virtual bool handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa);
	
	
	bool isActivated;
	bool isEditPoint;

	osgViewer::Viewer *mViewer;
	osg::Group *mRoot;
	osg::Group *tempGroup;//������ʱ��ͼ
	osg::Group *mapperGroup;
	osg::Group *editWallGroup;//�ɱ༭��ǽ�����������ڵ���
	osg::Group *tempEditGroup;
	InterfaceSigEventCallBack* iSigEventCallBack;

	std::vector<CPointWall> mvecBackCoord;
	std::vector<CPointWall> vecDropPoints;
	InterfaceSqliteDatabase* iSqliteDatabase;

	PGconn* conn;

	bool bRoofReady;
	std::vector<CLine> vecBuildingDLG;
	
	std::vector<osg::Vec3d> vecRoofPoint;
};