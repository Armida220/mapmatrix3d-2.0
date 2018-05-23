#pragma once
#include "OSG_Plus.h"
#include <vector>
#include "publicDefined.h"
#include "InterfaceUserEventCallBack.h"

class CSceneExtractWall
{
public:
	
	bool getTriangleSelect(std::vector<std::string>& vecChildFileName, osg::Vec4& color, osg::Matrix worldMatrix, osg::Vec3d worldPt, std::vector<osg::Vec3d> &vecIndex, std::vector<osg::Vec3d> &vecTriangle);			//��ȡѡ��������

	bool getTrianglePoints(osg::Geode* geode, osg::Matrix matrix, std::vector<osg::Vec3d> &vec, std::vector<osg::Vec3d> &vecIndex, osg::Vec4& color, double colorErr, osg::Vec3d normal, float ANGLE);				//���������Ƭ����

	bool getTrianglePointsEx(osg::Geode* geode, osg::Matrix matrix, std::vector<osg::Vec3d> &vec, std::vector<osg::Vec3d> &vecIndex, std::vector<osg::Vec4>& vecColor, double colorErr, std::vector<osg::Vec3d> & normal, float ANGLE);				//���������Ƭ����,������ʷ�����ж�

	int indexInTriangle(osg::Vec3d& pt, std::vector<osg::Vec3d>& vecPt);														//�������������

	bool isSamePt(osg::Vec3d& psrc, osg::Vec3d& pdst)//�ж��Ƿ�ͬһ��
	{
		return (psrc.x() == pdst.x()) && (psrc.y() == pdst.y()) && (psrc.z() == pdst.z());
	}

	void NormalVector(osg::Vec3d &a, osg::Vec3d &b, osg::Vec3d &c, osg::Vec3d &nomal);											//����������

	bool checkNomal(osg::Vec3d nom, osg::Vec3d normal, double m_normal, double err);											//���鷨����������������Ƿ�������ƫ����

	bool checkNomalEx(osg::Vec3d nom, std::vector<osg::Vec3d>& vecNormal, double err);                                          //���μ�����ʷ����������

	bool PtInTriangle(osg::Vec3d pt, osg::Vec3d& t1, osg::Vec3d& t2, osg::Vec3d& t3);											//�жϵ���������Ƭ��		

	bool triangleDrawed(osg::Vec3d& a, osg::Vec3d& b, osg::Vec3d& c, std::vector<osg::Vec3d> &vec);								//�����Ƿ��ظ�����

	int FindMinMax(std::vector<osg::Vec3d>& vec, osg::Vec3d& ptMinXY, osg::Vec3d& ptMaxXY, double& MinZ, double& MaxZ, double& MinX, double& MaxX, double& MinY, double& MaxY);

	void getPointProject(osg::Vec3d& pt, osg::Vec3d& ptPrj, PLane& pl);

	double getDisFromPointToPlane(osg::Vec3d& pt, PLane& plane);

	void getCoordBy2Point(osg::Vec3d& pt1, osg::Vec3d& pt3, std::vector<osg::Vec3d>& coord, PLane& plane);

	void redrawWall(osg::Vec3d& pt, osg::Vec3d& pt1,std::vector<osg::Vec3d>&vecCoord, WallInfo& wallSelected, osg::Vec4d color, osg::Group* group, osg::Group* tempGroup,osg::Matrix matrix);

	bool drawIntersectOfPlane(osg::Group* mapperGroup, osg::Group* tempGroup, std::vector<WallInfo> &planeSelect, osg::Vec4d& color, osg::Matrix& worldMatrix, InterfaceSigEventCallBack* iSigEventCallBack);

	bool isLineInMapperGroup(osg::Vec3d& p1, osg::Vec3d& p2, osg::Group* MapperGroup);

	void clearGroupResult(osg::Group* group);

	bool testColor(osg::Vec4& color1, osg::Vec4& color2, double err);

	bool testColorEx(osg::Vec4& color1, std::vector<osg::Vec4>& vecColor, double err);

	void getTextureCoordBy3Points(osg::Vec2d& pt1, osg::Vec2d& pt2, osg::Vec2d& pt3, std::vector<osg::Vec2d> &vec);

	void RGB2HSV(osg::Vec4& rgb,osg::Vec4& hsv);
};