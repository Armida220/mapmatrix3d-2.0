#pragma once

#include "BaseUserEvent.h"
#include "operationState.h"
#include "InterfaceUserEventCallBack.h"
#include "InterfaceOsgOrient.h"


class COsgAbsOrientEvent : public CBaseUserEvent
{
public:
	COsgAbsOrientEvent(osgViewer::Viewer *viewer, osg::Group *root,osg::Group *editGroup, InterfaceSigEventCallBack* iSigEventCallBack) : CBaseUserEvent(viewer)
	{
		mViewer = viewer;
		mRoot = root;
		mEditGroup = editGroup;

		this->iSigEventCallBack = iSigEventCallBack;
		isActivated = false;

		InterfaceOsgOrientFactory IAbsOrientFactory;
		IAbsOrient = IAbsOrientFactory.create();
	}

	virtual BOOL AbsOrient(std::string inFilePath);																//���Զ���
	
	virtual void UpdateActivatedStatus(std::vector<OperatingState> vecOpState);
	 
	virtual void LoadControlPt();																				//���ؿ��Ƶ�
	 
	virtual void ReclickCtrlPt(int ptNum);
	
	virtual void ReSetCtrlPtCheckStatus(int ptNum, bool isCheckPt);												//�������ü���

protected:
	virtual bool handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa);

protected:
	std::vector<osg::Vec3d> vecWorldCoord;

	osgViewer::Viewer *mViewer;
	osg::Group *mRoot;

	osg::Group *mEditGroup;
	InterfaceSigEventCallBack* iSigEventCallBack;
	InterfaceOsgOrient* IAbsOrient;

	//���Զ�����ת����
	osg::Matrix absMatrix;

	bool isActivated;
};