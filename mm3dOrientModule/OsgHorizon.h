#pragma once
#include "OSG_Plus.h"
#include "InterfaceOsgHorizon.h"


class COsgHorizon : public InterfaceOsgHorizon
{
public:
	void ModelHorizontalization(osg::ref_ptr<osg::Group> &sceneGroup);				//��ƽ����

	void ModelMirror(osg::ref_ptr<osg::Group> &sceneGroup);							//��������

	void ModelUpsideDown(osg::ref_ptr<osg::Group> &sceneGroup);						//�����ߵ�
};

