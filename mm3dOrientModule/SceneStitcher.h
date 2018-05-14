#pragma once
#include <string>
#include "OSG_Plus.h"

class CSceneStitcher
{
public:
	void SceneStitch(osg::ref_ptr<osg::Group> sceneGroup, std::vector<std::string> vecSceneFileName, 
		osg::ref_ptr<osg::Group> &combineGroup);															//����ƴ��

	void AdjustWholeSceneFlatPlaneXY(osg::ref_ptr<osg::Node> selectNode, double xMove, double yMove);	//ƽ�泡������							

	void AdjustWholeSceneHeight(osg::ref_ptr<osg::Node> selectNode, double zMove);						//�߶ȳ�������

	bool IsPathCorrect(std::vector<std::string> vecSceneFileName);										//�Ƿ����㳡��ƴ��·��Ҫ��

	void SceneSplit(osg::ref_ptr<osg::Node> sceneNode, std::string inFileName);							//�������

private:
	std::string ObtainFolderName(std::string inFileName);												//��ȡĿ¼��

	void ObtainDatabasePath(std::string inFileName, std::string &outFileName);							//��ȡ����·��
};

