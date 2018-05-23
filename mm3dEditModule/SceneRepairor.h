#pragma once
#include "OSG_Plus.h"
#include <vector>
#include "publicDefined.h"

class CSceneRepairor
{
public:
	CSceneRepairor(void);
	~CSceneRepairor(void);

	//�ӿ�
	osg::ref_ptr<osg::Node> createInterpolateRepairPatch(std::vector<osg::Vec3d> vecCoord, osg::Matrix worldMatrix, std::string imgFileName);	//������ֵ����

private:
	void InterpolatePt(osg::Geode& geode, osg::Matrix matrix, std::vector<osg::Vec3d> &vecPt, GridDem gDem, bool isRepair);						//��ֵ��

	osg::ref_ptr<osg::Node> createRepairPatch(std::vector<osg::Vec3d> vecCoord, std::string imageFileName);										//�����޲��ڵ�

	bool ObtainGeoRect(osg::ref_ptr<osg::Node> node, osg::Matrix matrix, std::vector<osg::Vec3d> &minMaxGeode);									//��ȡ���Χ
};





