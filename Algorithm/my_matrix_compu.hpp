#ifndef MY_MATRIX_COMPU_HPP
#define MY_MATRIX_COMPU_HPP


#include <math.h>
#include <iostream>

using namespace std;

//#ifndef DETMAXCOL
//#define DETMAXCOL 128//ע��ջ�Ĵ�С���ޣ�����ݹ���ȴ����ֵ��Ҫ��С
//#endif


//��������
template<class T>
void KfactorMatrix(T* M, int m, int n, T k, T* kM);

//����ӷ�
template<class T>
void AddMatrix(T* M1, T* M2, int m, int n, T* sumM);

//����˷�
template<class T>
void MatrixMuti1D(T* A1, int m1, int n1, T* A2, int m2, int n2, T* A3);

//m1��n1�� X m2��n2��
template<class T>
void MatrixMuti2D(int** a, int m1, int n1, int** b, int m2, int n2, int** c);

//��ӡ����
template<class T>
void PrintMatrix(T* M, int m, int n);

//���ؾ����Ӧ����Ϊij������ʽ������ʽ����(�Ǵ�������ʽ)��ֻ�з�������ʽ��������ʽ��nΪ�����������������
template<class T>
void MofDetofMatrix(T* M, int n, int i, int j, T* Mij);

//�����������ʽ��ֵ������һ��չ����nΪ����������������
template<class T>
T DetValueofMatrix(int n, T* M);

//�����İ������
template<class T>
void AdjointMatrix(T* M, int n, T* AM);

//�����ת��
template<class T>
void TransposeMatrix(T* M, int m, int n, T* TM);

//����������
template<class T>
void InverseMatrix(T* M, int n, T* IM);

//�����һ��
template<class T>
void NormMat(T* m, int r, int c);

#include "my_matrix_compu.template"
#endif