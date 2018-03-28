#pragma once
#include "InterfaceOsgExtractTexture.h"
#include "SceneExtractTexture.h"

class COsgExtractTexture : public InterfaceOsgExtractTexture
{
public:
	virtual osg::ref_ptr<osg::Node> ExtractTexture(std::vector<osg::Vec3d> vecWorldPt, osg::ref_ptr<osg::Node> sceneNode, double res);	//��ȡ����

	virtual osg::ref_ptr<osg::Image> ExtractTextureImage(std::vector<osg::Vec3d> vecWorldPt, osg::ref_ptr<osg::Node> sceneNode, double res); //��ȡ����Ӱ��
};