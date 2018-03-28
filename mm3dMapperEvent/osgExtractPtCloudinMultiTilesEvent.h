#pragma once
#include "BaseUserEvent.h"
#include "OSG_Plus.h"
#include "InterfaceUserEventCallBack.h"
#include <osgUtil/IntersectVisitor>
#include <osg/LineSegment>
#include <vector>
#include "TriangleRelation.h"
#include "InterfaceSqliteDatabase.h"

#define DLLAPI _declspec(dllexport)  



class DLLAPI COsgExtractPtCloudinMultiTilesEvent : public CBaseUserEvent
{
public:
	COsgExtractPtCloudinMultiTilesEvent(osgViewer::Viewer *viewer, osg::Group *root, osg::ref_ptr<osg::Group> MapperGroup, osg::ref_ptr<osg::Group> TempGroup, InterfaceSigEventCallBack* iSigEventCallBack) : CBaseUserEvent(viewer)
	{
		mViewer = viewer;
		mRoot = root;
		mapperGroup = MapperGroup;
		tempGroup = TempGroup;
		
		isActivated = false;
		ISigEventCallBack = iSigEventCallBack;

		//����database
		InterfaceSqliteDatabaseFactory iSqliteDatabaseFactory;
		iSqliteDatabase = iSqliteDatabaseFactory.create();
	}

protected:
	void UpdateActivatedStatus(std::vector<OperatingState> vecOpState);

	bool handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa);

	void clearGroupSafety(osg::Group* father, osg::Group* children);  //��ȫɾ���ڵ�

	void mouseMoveEvent(osg::Vec3d& worldPt,osg::NodePath np);

	bool getPointsInPolygon(string& str,osg::Vec3d& worldPt, double r);

	bool PtInTriangle(osg::Vec3d pt, osg::Vec3d& t1, osg::Vec3d& t2, osg::Vec3d& t3);

protected:

	bool isActivated;
	//��ײ�㣨������㣩
	std::vector<osg::Vec3d> vecSearchPoint;

	//�������
	std::vector<osg::Vec3d>  vecPtResult;
	std::vector<osg::Vec3d> vecEdge;
	//��������������������ɫ��
	std::vector<osg::Vec3d> vecNormal;
	std::vector<osg::Vec4> vecColor;

	//���ⲹ�����¼������ǹ�ϵ����߲���Ч��
	std::vector<std::string> vecFileNames;//�����Ѽ������ϵ�����ݿ�����
	std::vector<CTriangleRelation> vecTriangleRelation;//�������ǹ�ϵ

	osgViewer::Viewer *mViewer;
	osg::Group *mRoot;
	osg::Group *mapperGroup;
	osg::Group *tempGroup;	
	osg::Matrix worldMatrix;

	InterfaceSigEventCallBack* ISigEventCallBack;

	InterfaceSqliteDatabase* iSqliteDatabase;																					//sqlite3���ݿ�
};
