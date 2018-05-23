#pragma once
#include "BaseUserEvent.h"
#include "operationState.h"
#include "InterfaceUserEventCallBack.h"

class COsgHorizontalizationAccurateEvent : public CBaseUserEvent
{
public:
	COsgHorizontalizationAccurateEvent(osgViewer::Viewer *viewer, osg::Group *root, osg::ref_ptr<osg::Group> EditGroup, InterfaceSigEventCallBack* iSigEventCallBack) : CBaseUserEvent(viewer)
	{
		mViewer = viewer;
		mRoot = root;
		isActivated = false;
		this->iSigEventCallBack = iSigEventCallBack;
		editGroup = EditGroup;
	}

	bool handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa);

protected:
	void UpdateActivatedStatus(std::vector<OperatingState> vecOpState);

	void calcHorizonVector(std::vector<WallInfo>& planePara, osg::Vec3d& hVector);
	osgViewer::Viewer *mViewer;
	osg::Group *mRoot;
	osg::Group *editGroup;																										//������ʱ��ͼ
	InterfaceSigEventCallBack* iSigEventCallBack;
	osg::Matrix worldMatrix;
	osg::Vec3d hVector;
	bool isActivated;																											//ǽ���¼�����
	std::vector<WallInfo> planePara;
	std::vector<std::vector<osg::Vec3d> > vecTotalTriangle;																		//����������
};

