#pragma once
#include "BaseUserEvent.h"
#include "OSG_Plus.h"
#include "InterfaceUserEventCallBack.h"
#include "InterfaceOsgMapperEvent.h"

class COsgMapperEvent : public InterfaceOsgMapperEvent
{
public:
	COsgMapperEvent(osgViewer::Viewer *viewer, osg::Group *root, osg::ref_ptr<osg::Group> editGroup, osg::ref_ptr<osg::Group> interfaceGroup, osg::ref_ptr<osg::Group> TempGroup,
		osg::ref_ptr<osg::Group> linkGroup, osg::ref_ptr<osg::Group> DataGroup, InterfaceSigEventCallBack* iSigEventCallBack);

	virtual void addEventToViewer(osg::ref_ptr<osgViewer::Viewer> viewer);

	virtual void outForDxfAndShp(osg::Group *root);																//DXF���

	virtual bool extractContour(double high);																	//��ȡ�ȸ���			

	virtual void setPtCloudParameter(double angle, double alpha, double color);		                            //���õ�����ȡ��ز���

	virtual void getPtCloudParameter(double& angle, double& alpha, double& color);								//��õ�����ȡ��ز���

	virtual void extractContour(double zs, double ze, double zspan);

	virtual void getHatchParameter(double& step);

	virtual void setHatchParameter(double step);

private:
	std::vector<CBaseUserEvent*> vecMapperEvent;
};