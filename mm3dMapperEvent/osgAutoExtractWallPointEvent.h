#pragma once
#include "BaseUserEvent.h"
#include "OSG_Plus.h"
#include "InterfaceUserEventCallBack.h"
#include "InterfaceSqliteDatabase.h"
#include "PGControl.h"
#include "CDraggerPoint.h"
#include "Geometry.h"


class COsgAutoExtractWallPointEvent : public CBaseUserEvent
{
public:
	COsgAutoExtractWallPointEvent(osgViewer::Viewer *viewer, osg::Group *root, osg::ref_ptr<osg::Group> EditGroup, osg::ref_ptr<osg::Group> interfaceGroup, osg::ref_ptr<osg::Group> TempGroup, InterfaceSigEventCallBack* iSigEventCallBack) : CBaseUserEvent(viewer)
	{
		mViewer = viewer;
		mRoot = root;
		isActivated = false;
		this->iSigEventCallBack = iSigEventCallBack;
		mEditGroup = EditGroup;
		slotGroup = interfaceGroup;
		mTempGroup = TempGroup;
		conn = NULL;
	}

	bool handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa);

protected:
	void UpdateActivatedStatus(std::vector<OperatingState> vecOpState);

	void RegisterJScripts();
	
	void UnRegisterJScripts();

	void doBackSpaceEvent();
	void doSearchPointEvent(float x, float y, osg::NodePath np, osg::Vec3d worldPt, osg::Vec3d normal, std::vector<point3D>& vecLineRes);
	osgViewer::Viewer *mViewer;																									
	osg::Group *mRoot;
	osg::Group *mEditGroup;	 //������ʱ��ͼ
	osg::Group *slotGroup;//���ڽ��༭�ڵ�ӵ����ڵ���
	osg::Group *mTempGroup;
	InterfaceSigEventCallBack* iSigEventCallBack;
	osg::Matrix worldMatrix;
	bool isActivated;																											//ǽ���¼�����

	std::vector<std::vector<osg::Vec3d> > vecTotalTriangle;																		//����������

	InterfaceSqliteDatabase* iSqliteDatabase;																					//sqlite3���ݿ�

	PGconn* conn;
	std::string mEXEPath;

	std::vector<PLane> m_vecPlane;
	std::vector<osg::Vec3d> m_vecPlanePoint;
	std::vector<osg::Vec3d> m_vecContourPoint;

	std::vector<osg::Vec3d> m_vecPointOfLastWall;           //��¼�����һ����ĵ㼯
};

