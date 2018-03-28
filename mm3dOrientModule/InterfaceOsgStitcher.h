#pragma once
#include "OSG_Plus.h"

#ifdef OSGSTITCHLIBDLL  
#define OSGSTITCHAPI _declspec(dllexport)  
#else  
#define OSGSTITCHAPI  _declspec(dllimport)  
#endif  


class OSGSTITCHAPI InterfaceOsgStitcher
{
public:
	virtual void Stitch(osg::ref_ptr<osg::Group> sceneGroup, std::vector<std::string> vecSceneFileName, osg::ref_ptr<osg::Group> &combineGroup) = 0; //����ƴ��

	virtual bool IsPathCorrect(std::vector<std::string> vecSceneFileName) = 0;																		 //·���Ƿ���ȷ

	virtual void SceneSplit(osg::ref_ptr<osg::Node> sceneNode, std::string inFileName) = 0;															 //��������

	virtual void MoveWholeSceneXY(osg::ref_ptr<osg::Node> selectNode, double xMove, double yMove) = 0;												 //ƽ���ƶ�����

	virtual void MoveWholeSceneZ(osg::ref_ptr<osg::Node> selectNode, double zMove) = 0;																 //��ֱ�ƶ�����
};

class OSGSTITCHAPI InterfaceOsgStitcherFactory
{
public:
	InterfaceOsgStitcher* create();
};


