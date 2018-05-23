#ifndef PROJECTION_MATIRX_TRANSFORM
#define PROJECTION_MATIRX_TRANSFORM

#include <iostream>
#include <vector>

#include <highgui.h>
#include <cv.h>
#include <cxcore.h>

#include "coord.hpp"
#include "my_matrix_compu.hpp"
#include "QR.hpp"

using namespace std;



#define MY_PI 3.1415926535897932384626433832795

namespace transMat
{
	//�ɼ�����Ӿ���R����ֽ����̬�ǣ�ע����Ҫ��ת��
	void RtoAngle(double* R, double& phi, double& omega, double& kappa);

	//��̬��ת������Ӿ�����ת����
	void AngleToR(double f, double w, double k, double* R);

	//��K��R��C�����P����
	void CalculateP(double* K, double* R, double* C, double* P);

	//P����ֽ��K��R��C
	void CalculateKRC(double* P, double* K, double* R, double* C);

	//�ɽ���f�������㣬��������Ϊ��λ�������������Ͻ�Ϊԭ�㣬����K����
	void CalculateK(double f, double x0, double y0, double* K);

	//������ת����P����ֱ��ת������Ƭ����Ϊԭ���P����
	void SixParmToP(double f, double x0, double y0, CoordDouble3D& xyz, CoordDouble3D& fwk, double* P);

	//��P�������ά��������ά����
	void Point3dToPoint2d(double* P, CoordDouble3D xyz, CoordDouble2D& xy);

	//��f��R��C����ccd���ĵ�����
	void CalculateCCDCenter(double f, double* R, double* C, CoordDouble3D& xyz_ccd_center);
}


#endif