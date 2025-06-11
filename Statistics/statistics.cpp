// statistics.cpp
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "MyRand.h"
using namespace std;

void GetUniformData(double *array, int n, double a=0, double b=1);			// ���ɷ��Ӿ��ȷֲ��������
void GetGaussData(double *array, int n, double mean=0, double variance=1);	// ���ɷ�����̬�ֲ��������
double Mean(const double *array, int n);									// �����ֵ
double Variance(const double *array, int n);								// ���㷽��
double Range(const double *array, int n, double &max, double &min);			// ���㼫����ֵ-��Сֵ��
	
int TestU(double a=54, double b=90)				// ����[54, 90]�ϵľ��ȷֲ�
{
	const int N=100000;
	double array[N]; 
				// �������飬������һ������"�㹻��"�����������ڴ��һϵ������
	double mean, var, range, max, min;
				// ��ֵ�����������ֵ����Сֵ

	cout << "\n*** [" << a << ", " << b << "]�Ͼ��ȷֲ����ԡ�"
		 << "ע:����[a, b]�Ͼ��ȷֲ�����������ľ�ֵΪ (a+b)/2 = " << (a+b)/2
		 << "������Ϊ (b-a)^2/12 = " << (b-a)*(b-a)/12 << endl;			// �������ֵ
	for(int n=10; n<=N; n*=10)
	{
		GetUniformData(array, n, a, b);			// ����������һ������
		mean = Mean(array, n);
		var = Variance(array, n);
		range = Range(array, n, max, min);
												// ��3��4���������������Ѿ����ڵı���
		cout << "\n���ݹ�ģ n = " << n									// �������ֵ
			 << "\n��ֵ: " << mean
			 << "\n����: " << var
			 << "\n����: " << range << "\t[" << min << ", " << max << "]" << endl;
	}
	return 0;
}

int TestN(double m0=72, double v0=6*6)			// ������̬�ֲ�
{
	const int N=100000;
	double array[N]; 
				// �������飬������һ������"�㹻��"�����������ڴ��һϵ������
	double mean, var, range, max, min;
				// ��ֵ�����������ֵ����Сֵ

	cout << "\n*** ��̬�ֲ�������˹�ֲ���N(��, ��*��)���ԡ����о�ֵ��="<< m0 << ", " << "�����*��=" << v0 << endl;
	for(int n=10; n<=N; n*=10)
	{
		GetGaussData(array, n, m0, v0);			// ����������һ������
		mean = Mean(array, n);
		var = Variance(array, n);
		range = Range(array, n, max, min);
												// ��3��4���������������Ѿ����ڵı���
		cout << "\n���ݹ�ģ n = " << n
			 << "\n��ֵ: " << mean
			 << "\n����: " << var
			 << "\n����: " << range << "\t[" << min << ", " << max << "]"
			 << "\n[��-3��, ��+3��] = [" << mean-3*sqrt(var) << ", " << mean+3*sqrt(var) << "]" << endl;
	}
	return 0;
}

int main()
{
	srand(time(NULL));					// ���������������������

	TestU();
	TestN();		// TestN(75, 25);
	return 0;
}

void GetUniformData(double *array, int n, double a, double b)
{
	for(int i=0; i<n; i++)
		array[i] = UniformRand(a, b);
}

void GetGaussData(double *array, int n, double mean, double variance)
{
	for(int i=0; i<n; i++)
		array[i] = GaussRand(mean, variance);
}

double Mean(const double *array, int n)			// �����ֵ
{
	double sum=0;
	for(int i=0; i<n; i++)
		sum += array[i];
	return sum/n;
}

double Variance(const double *array, int n)		// ���㷽��
{					// �����㷽��Ĺ�ʽ��һ������
	double y=0, z=0;
	for(int i=0; i<n; i++)
	{
		y += array[i];
		z += array[i]*array[i];
	}
	y /= n;
	z /= n;
	return z - y*y;
/*	
	double s=0, t, mean=Mean(array, n);
	for(int i=0; i<n; i++)
	{
		t = array[i]-mean;		// ����t���ټ�����
		s += t*t;				// (array[i]-mean)*(array[i]-mean)
	}
	return s/n;
*/
}

double Range(const double *array, int n, double &max, double &min)	// ���㼫��
{
	min = max = array[0];
	for(int i=1; i<n; i++)
	{
		if(array[i]<min) min = array[i];
		if(array[i]>max) max = array[i];
	}
	return max-min;
}
