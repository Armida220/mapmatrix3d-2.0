#pragma once

#include "InterfaceBaseDrawer.h"
#include "BaseUserEvent.h"
#include "operationState.h"
#include "InterfaceUserEventCallBack.h"

class COsgSceneMatchEvent : public CBaseUserEvent
{
public:
	COsgSceneMatchEvent(osgViewer::Viewer *viewer, osg::Group *root, osg::Group* editGroup, InterfaceSigEventCallBack* iSigEventCallBack);

	virtual void UpdateActivatedStatus(std::vector<OperatingState> vecOpState);

	virtual void MatchSingleModel();																							//����ƥ��

protected:
	virtual bool handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa);

private:
	std::vector<osg::Vec3d> vecWorldCoord;

	osgViewer::Viewer *mViewer;
	osg::Group *mRoot;
	osg::Group* mEditGroup;

	InterfaceSigEventCallBack* iSigEventCallBack;

	//ģ��ƥ��
	std::vector<osg::Vec3d> vecRelaCoord;
	std::vector<osg::Vec3d> vecAbsCoord;

	//���Զ�����ת����
	osg::Matrix absMatrix;

	bool isActivated;
};