#pragma once
#include <vector>
#include "coord.hpp"
#include "InterfaceOsgAlgorithm.h"


class OSGALGORITHMAPI CSevenParameter
{
public:
	CSevenParameter();
	~CSevenParameter();

	void LoadControlPoints(std::vector<CoordDouble3D>& X_a, std::vector<CoordDouble3D>& X_r);
	//�����߲���
	void CalculateSevenParameter();
	//����ص��������ת����������
	void CalculateRelativeToAbsolute(CoordDouble3D X_r, CoordDouble3D& X_a);
	//����Զ����P�����е�R��C��������Զ����P�����е�R��C
	void CalculateAbsoluteRC(double* R_r, double* C_r, double* R_a, double* C_a);

	//�߲���
	double R_[9];
	double t_[3];
	double s_;
	//��ص��������
	std::vector<CoordDouble3D> X_a_;
	//��ص��������
	std::vector<CoordDouble3D> X_r_;
	//��ʾ�Ƿ��Ѿ��������߲���
	bool seven_parm_is_exist_;
};

