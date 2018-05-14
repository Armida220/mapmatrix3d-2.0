#pragma once
#include "OSG_Plus.h"
#include "InterfaceUserEventCallBack.h"
#include "publicDefined.h"

#ifdef EXTRACTOBJECTLIBDLL  
#define EXTRACTOBJECTAPI _declspec(dllexport)  
#else  
#define EXTRACTOBJECTAPI  _declspec(dllimport)  
#endif  


class EXTRACTOBJECTAPI InterfaceCOsgExtractObject
{
public:
	//�ӿ�
	virtual bool ExtractBottomObjectByScope(osg::ref_ptr<osg::Node> sceneNode, osg::ref_ptr<osg::Group> root, std::string inFilePathName, std::string outputObjectFilePathName, 
		std::vector<CScope> vecScope, osg::ref_ptr<osg::MatrixTransform> &mTrans, InterfaceSigEventCallBack* iSigEventCallBack) = 0;		//����Χ��ȡ��ײ��ģ�� ��������

	virtual bool AccurateClipBottomScene(osg::ref_ptr<osg::Node> sceneNode, std::vector<CScope> vecScope, osg::ref_ptr<osg::MatrixTransform> &mTrans,bool bAccurate = true) = 0;
};

class EXTRACTOBJECTAPI InterfaceCOsgExtractObjectFactory
{
public:
	InterfaceCOsgExtractObject* create();

};

