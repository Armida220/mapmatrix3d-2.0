#include "stdafx.h"
#include "OsgExtractArea.h"
#include "AccurateClipper.h"
#include "InterfaceOsgFinder.h"
#include "InterfaceOsgEditor.h"

void COsgExtractArea::extractArea(osg::ref_ptr<osg::Node> sceneNode, std::string inFilePathName, std::vector<CScope> vecScope)
{
	//����Χ��ȷ�и�
	CAccurateClipper clipper(sceneNode, vecScope);
	osg::ref_ptr<osg::MatrixTransform> mTrans = new osg::MatrixTransform;
	clipper.clipBottomScene(mTrans);

	//�ѵ�����볡��
	objectAdder.addObjectToScene(sceneNode, mTrans);
}

osg::ref_ptr<osg::Node> COsgExtractArea::extractObjectByArea(osg::ref_ptr<osg::Node> sceneNode, std::vector<CScope> vecScope)
{
	//����Χ��ȷ�и�
	CAccurateClipper clipper(sceneNode, vecScope);
	osg::ref_ptr<osg::MatrixTransform> mTrans = new osg::MatrixTransform;
	clipper.clipBottomScene(mTrans);

	return mTrans.get();
}