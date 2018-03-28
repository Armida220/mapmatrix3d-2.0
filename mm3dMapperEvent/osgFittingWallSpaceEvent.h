#pragma once
#include "BaseUserEvent.h"
#include "operationState.h"
#include "InterfaceUserEventCallBack.h"
#include <osgManipulator/Translate2DDragger>
#include <osgManipulator/Command>
#include <osgManipulator/CommandManager> 
#include "CDraggerPoint.h"
#include "InterfaceSqliteDatabase.h"
#include "InterfaceOsgExtractWall.h"
#include "SceneExtractWall.h"
#include <vector>

using namespace std;

class COsgFittingWallSpaceEvent : public CBaseUserEvent
{
public:
	COsgFittingWallSpaceEvent(osgViewer::Viewer *viewer, osg::Group *root, osg::ref_ptr<osg::Group> editGroup, osg::ref_ptr<osg::Group> interfaceGroup, osg::ref_ptr<osg::Group> TempGroup,  
		InterfaceSigEventCallBack* iSigEventCallBack) : CBaseUserEvent(viewer)
	{
		mViewer = viewer;
		mRoot = root;
		isActivated = false;
		this->iSigEventCallBack = iSigEventCallBack;
		tempGroup = TempGroup;
		editWallGroup = editGroup;
		slotGroup = interfaceGroup;
		vecCoord.clear();
		_activeDragger = 0;
		atWall = false;

		
		//����database
		InterfaceSqliteDatabaseFactory iSqliteDatabaseFactory;
		iSqliteDatabase = iSqliteDatabaseFactory.create();
		sqlite3* db = iSqliteDatabase->OpenDatabase("runData.db");
		iSqliteDatabase->create_Table(db, "create Table Wall(a, b, c, d, x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4, angle,err,normal);");
		iSqliteDatabase->ClearAllRecord(db, "delete from Wall");
		iSqliteDatabase->CloseDatabase(db);
	}

protected:
	void UpdateActivatedStatus(std::vector<OperatingState> vecOpState);

	virtual bool handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa);
	
	bool pushEvent(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa);
	
	

protected:
	std::vector<osg::Vec3d> vecCoord;
	
	std::vector<osg::Vec3d>  vecTotalTriangle;
	
	std::vector<WallInfo> planePara;//���е���
	
	osgViewer::Viewer *mViewer;
	osg::Group *mRoot;
	
	osg::Group *tempGroup;//������ʱ��ͼ
	osg::Group *editWallGroup;//�ɱ༭��ǽ�����������ڵ���
	osg::Group *slotGroup;//���ڽ��༭�ڵ�ӵ����ڵ���
	InterfaceSigEventCallBack* iSigEventCallBack;

	bool atWall;
	bool isActivated;

	osg::Matrix worldMatrix;
	osg::Vec3d worldPt;
	osg::Vec3d normal;

	osg::Vec3d partnerPoint;
	osg::Vec3d endPoint;
	std::vector<string> vecWall;
	
	WallInfo wallSelected;

	//�϶�ƽ���������
	osgManipulator::PointerInfo _pointer;
	CDraggerPoint* _activeDragger;

	
	InterfaceSqliteDatabase* iSqliteDatabase;																					//sqlite3���ݿ�
};