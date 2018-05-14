#pragma once
#include "OSG_Plus.h"
#include "InterfaceUserEventCallBack.h"

#ifdef MAPPEREVENTLIBDLL  
#define MAPPEREVENTAPI _declspec(dllexport)  
#else  
#define MAPPEREVENTAPI  _declspec(dllimport)  
#endif 

class MAPPEREVENTAPI InterfaceOsgMapperEvent
{
public:
	virtual void addEventToViewer(osg::ref_ptr<osgViewer::Viewer> viewer) = 0;

	virtual void outForDxfAndShp(osg::Group *root) = 0;																//DXF���

	virtual bool extractContour(double high) = 0;																	//��ȡ�ȸ���			

	virtual void setPtCloudParameter(double angle, double alpha, double color) = 0;		                            //���õ�����ȡ��ز���

	virtual void getPtCloudParameter(double& angle, double& alpha, double& color) = 0;								//��õ�����ȡ��ز���

	virtual void extractContour(double zs, double ze, double zspan) = 0;

	virtual void getHatchParameter(double& step) = 0;

	virtual void setHatchParameter(double step) = 0;
};

class MAPPEREVENTAPI InterfaceOsgMapperEventFactory
{
public:
	InterfaceOsgMapperEvent* create(osgViewer::Viewer *viewer, osg::Group *root, osg::ref_ptr<osg::Group> editGroup, osg::ref_ptr<osg::Group> interfaceGroup,
		osg::ref_ptr<osg::Group> TempGroup, osg::ref_ptr<osg::Group> linkGroup , osg::ref_ptr<osg::Group> DataGroup, InterfaceSigEventCallBack* iSigEventCallBack);

};