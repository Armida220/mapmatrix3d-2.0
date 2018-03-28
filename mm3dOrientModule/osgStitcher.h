#pragma once
#include "InterfaceOsgStitcher.h"


class COsgStitcher : public InterfaceOsgStitcher
{
public:
	void Stitch(osg::ref_ptr<osg::Group> sceneGroup, std::vector<std::string> vecSceneFileName, osg::ref_ptr<osg::Group> &combineGroup); //����ƴ��

	bool IsPathCorrect(std::vector<std::string> vecSceneFileName);																		 //·���Ƿ���ȷ

	void SceneSplit(osg::ref_ptr<osg::Node> sceneNode, std::string inFileName);															 //��������

	void MoveWholeSceneXY(osg::ref_ptr<osg::Node> selectNode, double xMove, double yMove);												 //ƽ���ƶ�����

	void MoveWholeSceneZ(osg::ref_ptr<osg::Node> selectNode, double zMove);																 //��ֱ�ƶ�����
};