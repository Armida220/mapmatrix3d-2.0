#pragma once
#include "BaseUserEvent.h"
#include "operationState.h"
#include "InterfaceUserEventCallBack.h"
#include "InterfaceOsgFinder.h"
#include <vector>


class COsgDrawHorizLineEvent : public CBaseUserEvent
{
public:
	COsgDrawHorizLineEvent(osgViewer::Viewer *viewer, osg::Group *root, osg::ref_ptr<osg::Group> MapperGroup, osg::ref_ptr<osg::Group> TempGroup, InterfaceSigEventCallBack* iSigEventCallBack) : CBaseUserEvent(viewer)
	{
		mViewer = viewer;
		mRoot = root;
		isActivated = false;
		this->iSigEventCallBack = iSigEventCallBack;

		tempGroup = TempGroup;
		mapperGroup = MapperGroup;


	}
protected:
	void UpdateActivatedStatus(std::vector<OperatingState> vecOpState);
	virtual bool handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa);
	
	bool isActivated;
	osgViewer::Viewer *mViewer;
	osg::Group *mRoot;
	osg::Group *tempGroup;//������ʱ��ͼ
	osg::Group *mapperGroup;//�ɱ༭��ǽ�����������ڵ���
	osg::Matrix worldMatrix;
	InterfaceSigEventCallBack* iSigEventCallBack;

	vector<osg::Vec3d> vecCoord;
	std::vector<LineInfo> vecLine;//�洢mapperGroup�л��Ƶ�ֱ��
	std::vector<char*> vecName;//�����߶�����

	double horiz_high;
	bool islineStart;
};
