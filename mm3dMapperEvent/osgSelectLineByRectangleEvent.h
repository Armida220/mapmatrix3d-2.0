#pragma once
#include "BaseUserEvent.h"
#include "operationState.h"
#include "InterfaceUserEventCallBack.h"
#include "InterfaceOsgFinder.h"
#include "Geometry.h"

class COsgSelectLineByRectangleEvent :  public CBaseUserEvent
{
public:
	COsgSelectLineByRectangleEvent(osgViewer::Viewer *viewer, osg::Group *root, osg::ref_ptr<osg::Group> MapperGroup, InterfaceSigEventCallBack* iSigEventCallBack) :  CBaseUserEvent(viewer)
	{
		mViewer = viewer;
		mRoot = root;
		isActivated = false;
		this->iSigEventCallBack = iSigEventCallBack;
		mapperGroup = MapperGroup;
		isFirstPoint = true;
	}

protected:
	virtual bool handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa);

	bool CtrlReleaseSelectLineByRectangle(osg::ref_ptr<osg::Group> MapperGroup, std::vector<osg::Vec3d> &vecWorldCoord, osg::Vec3d worldPt, osg::Matrix viewMatrix, 
		std::vector<std::vector<osg::MatrixTransform*>> &VecHighLightTrans);																										//ctrl + �ͷ�ѡ����

	void COsgDeleteSelectLine(osg::ref_ptr<osg::Group> MapperGroup, std::vector<std::vector<osg::MatrixTransform*>> &VecHighLightTrans);											//ɾ��ѡ����	

	void UpdateActivatedStatus(std::vector<OperatingState> vecOpState);

	void HighLightLineInRectangle(osg::ref_ptr<osg::Group> MapperGroup, std::vector<CL::Vec2d> pol, std::vector<std::vector<osg::MatrixTransform*>> &VecHighLightTrans);		//�����ھ����ڵ���

	void CancelHighLightLineForAll(osg::ref_ptr<osg::Group> MapperGroup, std::vector<std::vector<osg::MatrixTransform*>> &VecHighLightTrans);									//ȡ��ȫ������
		
	void BackSpaceCancelHighLightLineInRectangle(std::vector<std::vector<osg::MatrixTransform*>> &VecHighLightTrans);															//ȡ����Χ�ڵĸ���		

protected:
	osgViewer::Viewer *mViewer;
	osg::Group *mRoot;
	osg::Group *mapperGroup;

	std::vector<std::vector<osg::MatrixTransform*>> vecHighLightTrans;

	InterfaceSigEventCallBack* iSigEventCallBack;
	std::vector<osg::Vec3d> vecWorldCoord;
	osg::Matrix worldMatrix;
	osg::Vec3d worldPt;
	bool isActivated;
	bool isFirstPoint;
};