#pragma once
#include "OSG_Plus.h"
#include "InterfaceOsgFinder.h"

class COsgEditLine
{
public:
	int getGroupPoints(osg::Vec3d& worldPt, double dis, osg::Group * mapperGroup, std::vector<osg::Vec3d>& vecPoints);

	void getTerminal(osg::Vec3d& worldPt,  std::vector<osg::Vec3d>& vecPoints);  //�㼯����������ĵ�

	//ȥ������֮��ĵ�  Ĭ�ϱ����ϳ���
	void cutLine(osg::Vec3d p1, osg::Vec3d p2, std::vector<osg::Vec3d>& vecPoints, std::vector<osg::Vec3d>& vecAddPoints, std::vector<osg::Vec3d>& vecReserveL, std::vector<osg::Vec3d>& vecReserveS);

	void linkVector(std::vector<osg::Vec3d>& vec1, std::vector<osg::Vec3d>& vec2, std::vector<osg::Vec3d>& vecPt);
};