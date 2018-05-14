#pragma once
#include "BaseUserEvent.h"
#include "operationState.h"
#include "InterfaceUserEventCallBack.h"
#include "InterfaceOsgFinder.h"
#include <vector>


class COsgExtractLineInsectEvent : public CBaseUserEvent
{
public:
	COsgExtractLineInsectEvent(osgViewer::Viewer *viewer, osg::Group *root, osg::ref_ptr<osg::Group> MapperGroup, osg::ref_ptr<osg::Group> TempGroup, InterfaceSigEventCallBack* iSigEventCallBack) : CBaseUserEvent(viewer)
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
	InterfaceSigEventCallBack* iSigEventCallBack;

	vector < osg::Vec3d > vecCoord;
	char* transName1, *transName2;//���߶�����
	std::vector<LineInfo> vecLineforInsect;//�߶���ר��
	osg::ref_ptr<osg::MatrixTransform> selectTrans1, selectTrans2;//�洢�󽻵������߶�
	osg::Vec3d PointInLine1, PointInLine2;//�洢�󽻵������˵�

	osg::Matrix worldMatrix;
};