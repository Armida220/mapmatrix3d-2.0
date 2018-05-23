#pragma once
#include "BaseUserEvent.h"
#include "operationState.h"
#include "InterfaceUserEventCallBack.h"


class COsgExtractAccuraOutLineEvent : public CBaseUserEvent
{
public:
	COsgExtractAccuraOutLineEvent(osgViewer::Viewer *viewer, osg::Group *root, osg::ref_ptr<osg::Group> MapperGroup, osg::ref_ptr<osg::Group> TempGroup,InterfaceSigEventCallBack* iSigEventCallBack) :  CBaseUserEvent(viewer)
	{
		mViewer = viewer;
		mRoot = root;
		isActivated = false;
		this->iSigEventCallBack = iSigEventCallBack;
		mapperGroup = MapperGroup;
		tempGroup = TempGroup;

		vecWorldCoord.clear();
		isArea = true;
		isStart = false;
	}

	void UpdateActivatedStatus(std::vector<OperatingState> vecOpState);

	bool DrawOutline(osg::Vec3d worldPt, std::vector<osg::Vec3d> vecWorldCoord, osg::ref_ptr<osg::Group> root, osg::Matrix WorldMatrix);
	bool startDrawOutline(osg::Vec3d worldPt, std::vector<osg::Vec3d> vecWorldCoord, osg::ref_ptr<osg::Group> root, osg::Matrix WorldMatrix);
	bool reSet();//��λ ��ʼ����Χ

protected: 
	virtual bool handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa);
	
	
protected:
	std::vector<osg::Vec3d> vecWorldCoord;

	osgViewer::Viewer *mViewer;
	osg::Group *mRoot;
	osg::Group *mapperGroup;
	osg::Group *tempGroup;

	bool isStart;//�Ƿ�ʼ������
	bool isArea;//�Ƿ�ʼ����Χ
	InterfaceSigEventCallBack* iSigEventCallBack;

	//���Զ�����ת����
	bool isActivated;
};