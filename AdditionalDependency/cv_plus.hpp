#ifndef CV_PLUS_HPP
#define CV_PLUS_HPP

#include <iostream>
#include <vector>
#include <highgui.h>
#include <cv.h>
#include <cxcore.h>

using namespace std;



void cvmPrint(CvMat* M);
//����ָ������
void cvmZero(CvMat* M);
//��ָ����������Ԫ�ظ�ֵval
void cvmSetVal(CvMat* M, double val);
//�����������Ԫ�ص�ƽ����
double cvmNorm2(CvMat* M);

//����������M1��Դ��M2��Ŀ��
void cvmVectorCopy(vector<CvMat* >& M1, vector<CvMat* >& M2);

//�½�����������M1��Դ��M2��Ŀ�꣬������ʱ���ʼ��M2
void cvmVectorNewCopy(vector<CvMat* >& M1, vector<CvMat* >& M2);

void cvReleaseVectorMat(vector<CvMat* >& M);

#endif