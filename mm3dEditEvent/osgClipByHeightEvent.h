#pragma once

#include "BaseUserEvent.h"
#include "operationState.h"
#include "InterfaceUserEventCallBack.h"


class COsgClipByHeightEvent : public CBaseUserEvent
{
public:
	COsgClipByHeightEvent(osgViewer::Viewer *viewer, osg::Group *root, InterfaceSigEventCallBack* iSigEventCallBack) : CBaseUserEvent(viewer)
	{
		mViewer = viewer;
		mRoot = root;

		this->iSigEventCallBack = iSigEventCallBack;
		isActivated = false;
		reFactor = 1;
		clipHeight = 0;
	}

	virtual void ClipHeight();																												//�ӿ� ���߶Ȳ���

	virtual void InvertClipByHeight();																										//�ӿ� ���෴�߶Ƚ��в���

protected:
	virtual bool handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa);

	virtual void UpdateActivatedStatus(std::vector<OperatingState> vecOpState);

	virtual void KeyDownMoveClipByHeight(double moveY, double reFactor, osg::ref_ptr<osg::Group> mSceneGroup);

	virtual void KeyCtrlZReverseClipByHeight(osg::ref_ptr<osg::Group> mSceneGroup);

protected:
	osgViewer::Viewer *mViewer;
	osg::Group *mRoot;

	InterfaceSigEventCallBack* iSigEventCallBack;

	//��������
	double reFactor;
	double clipHeight;

	bool isActivated;
};