#pragma once
#include "OSG_Plus.h"

class CSceneHorizoner
{
public:
	CSceneHorizoner(void);
	~CSceneHorizoner(void);
	//�ӿ�
	void StartModelHorizontalization(osg::ref_ptr<osg::Group>& sceneGroup);				//��ʼ���г�����ƽ

	//�ӿ�	
	void ModelMirror(osg::ref_ptr<osg::Group> &ceneGroup);								//��������

	//�ӿ�
	void ModelUpsideDown(osg::ref_ptr<osg::Group> &sceneGroup);							//�����ߵ�

private:
	void CalculateSceneRotMat(osg::ref_ptr<osg::Node> sceneNode, osg::Matrix &matrix);	//���㳡������ת����
};

