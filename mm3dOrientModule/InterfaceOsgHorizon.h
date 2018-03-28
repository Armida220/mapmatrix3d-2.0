#pragma once
#include "OSG_Plus.h"

#ifdef HORIZONLIBDLL  
#define HORIZONAPI _declspec(dllexport)  
#else  
#define HORIZONAPI  _declspec(dllimport)  
#endif  

class HORIZONAPI InterfaceOsgHorizon
{
public:
	virtual void ModelHorizontalization(osg::ref_ptr<osg::Group> &sceneGroup) = 0;				//��ƽ����

	virtual void ModelMirror(osg::ref_ptr<osg::Group> &sceneGroup) = 0;							//��������

	virtual void ModelUpsideDown(osg::ref_ptr<osg::Group> &sceneGroup) = 0;						//�����ߵ�
};


class HORIZONAPI InterfaceOsgHorizonFactory
{
public:
	InterfaceOsgHorizon* create();
};

