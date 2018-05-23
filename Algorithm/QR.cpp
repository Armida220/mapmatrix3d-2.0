#include "stdafx.h"
#include "QR.hpp"

//���������
double dot(double* a, double* b, int n)
{
	double sum = 0.0;
	for (int i = 0; i < n; i++)
	{
		sum += a[i] * b[i];
	}
	return sum;
}

//�������ӷ�
void add(double* dst, double* src, int n)
{
	for (int i = 0; i < n; i++)
	{
		dst[i] += src[i];
	}
}

//����������ϵ��
double* kMultV(double cof, double* v, int n)
{
	double* kv = new double[n];
	for (int i = 0; i < n; i++)
	{
		kv[i] = cof * v[i];
	}
	return kv;
}


void getGama(int n, double* beta, double* gama)
{
	double fenmu = sqrt(dot(beta, beta, n));
	for (int i = 0; i < n; i++)
	{
		gama[i] = beta[i] / fenmu;
	}
}

//��ʩ����������������QR�ֽ�
void myQR(double* A, int n, double* Q, double* R)
{
	//�洢A��ÿһ������
	double** alpha = new double*[n];
	for (int i = 0; i < n; i++)
	{
		alpha[i] = new double[n];
	}
	for (int col = 0; col < n; col++)
	{
		for (int row = 0; row < n; row++)
		{
			alpha[col][row] = A[row * n + col];
		}
	}

	//����beta��gama
	double** beta = new double*[n];
	for (int i = 0; i < n; i++)
	{
		beta[i] = new double[n];
	}
	double** gama = new double*[n];
	for (int i = 0; i < n; i++)
	{
		gama[i] = new double[n];
	}
	for (int i = 0; i < n; i++) //��i��beta��gama
	{
		if (i == 0)
		{
			memcpy(beta[i], alpha[i], n * sizeof(double));
			getGama(n, beta[i], gama[i]);
		}
		else
		{
			double* agg = new double[n];
			memcpy(agg, alpha[i], n * sizeof(double));
			for (int j = 0; j <= i - 1; j++)
			{
				double cof = -1.0 * dot(alpha[i], gama[j], n);
				double* tmp = kMultV(cof, gama[j], n);
				add(agg, tmp, n);
				delete []tmp;
			}
			memcpy(beta[i], agg, n * sizeof(double));
			getGama(n, beta[i], gama[i]);
			delete []agg;
		}
	}

	//�洢Q��R
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			Q[i * n + j] = gama[j][i];
		}
	}

	memset(R, 0.0, n * n * sizeof(double));
	for (int i = 0; i < n; i++)
	{
		for (int j = i; j < n; j++)
		{
			if (j == i)
			{
				R[i * n + j] = sqrt(dot(beta[i], beta[i], n));
			}
			else
			{
				R[i * n + j] = dot(alpha[j], gama[i], n);
			}
		}
	}

	for (int i = 0; i < n; i++)
	{
		delete []alpha[i];
	}
	delete []alpha;
	for (int i = 0; i < n; i++)
	{
		delete []beta[i];
	}
	delete []beta;
	for (int i = 0; i < n; i++)
	{
		delete []gama[i];
	}
	delete []gama;
}
