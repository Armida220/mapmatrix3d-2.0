#pragma once
#include "cv_plus.hpp"
#include "Geometry.h"

#ifdef OSGALGORITHMLIBDLL  
#define OSGALGORITHMAPI _declspec(dllexport)  
#else  
#define OSGALGORITHMAPI  _declspec(dllimport)  
#endif  


class OSGALGORITHMAPI InterfaceOsgAlgorithm
{
public:
	virtual void CvmPrint(CvMat* M) = 0;																	//��ӡ����

	virtual void RtoAngle(double* R, double& phi, double& omega, double& kappa) = 0;						//��ת�����ɽǶ�

	virtual void AngleToR(double f, double w, double k, double* R) = 0;										//�Ƕ�ת��ת����

	virtual bool PointInPolygon2D(double x, double y, const vector<CL::Vec2d> &POL) = 0;					//���ڶ������

	virtual bool DoesPolygonIntersetPolygon(std::vector<CL::Vec2d> pol1, std::vector<CL::Vec2d> pol2) = 0;	//�����Ƿ��ཻ

	virtual bool FindMinMaxHeight(std::vector<osg::Vec3d> vecPt, double &minHeight, double &maxHeight) = 0;	//���������С�߶�
};


class OSGALGORITHMAPI InterfaceOsgAlgorithmFactory
{
public:
	InterfaceOsgAlgorithm* create();
};

