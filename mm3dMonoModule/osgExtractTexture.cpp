// osgExtractTexture.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "osgExtractTexture.h"

osg::ref_ptr<osg::Node> COsgExtractTexture::ExtractTexture(std::vector<osg::Vec3d> vecWorldPt, osg::ref_ptr<osg::Node> sceneNode, double res)
{
	CSceneExtractTexture sceneExtractTexture;
	osg::ref_ptr<osg::Node> node = sceneExtractTexture.extractTexture(vecWorldPt, sceneNode, res);
	return node.get();
}


osg::ref_ptr<osg::Image> COsgExtractTexture::ExtractTextureImage(std::vector<osg::Vec3d> vecWorldPt, osg::ref_ptr<osg::Node> sceneNode, double res)
{
	CSceneExtractTexture sceneExtractTexture;
	osg::ref_ptr<osg::Image> image = sceneExtractTexture.ExtractTextureImage(vecWorldPt, sceneNode, res);
	return image.get();
}