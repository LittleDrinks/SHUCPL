// statistics.cpp
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "MyRand.h"
using namespace std;

void GetUniformData(double *array, int n, double a=0, double b=1);			// 生成服从均匀分布的随机数
void GetGaussData(double *array, int n, double mean=0, double variance=1);	// 生成服从正态分布的随机数
double Mean(const double *array, int n);									// 计算均值
double Variance(const double *array, int n);								// 计算方差
double Range(const double *array, int n, double &max, double &min);			// 计算极差（最大值-最小值）
	
int TestU(double a=54, double b=90)				// 测试[54, 90]上的均匀分布
{
	const int N=100000;
	double array[N]; 
				// 定义数组，即设置一个容量"足够的"的容器，用于存放一系列数据
	double mean, var, range, max, min;
				// 均值、方差、极差、最大值、最小值

	cout << "\n*** [" << a << ", " << b << "]上均匀分布测试。"
		 << "注:服从[a, b]上均匀分布的随机变量的均值为 (a+b)/2 = " << (a+b)/2
		 << "，方差为 (b-a)^2/12 = " << (b-a)*(b-a)/12 << endl;			// 输出理论值
	for(int n=10; n<=N; n*=10)
	{
		GetUniformData(array, n, a, b);			// 数组容器不一定用满
		mean = Mean(array, n);
		var = Variance(array, n);
		range = Range(array, n, max, min);
												// 第3、4两个参数必须是已经存在的变量
		cout << "\n数据规模 n = " << n									// 输出测试值
			 << "\n均值: " << mean
			 << "\n方差: " << var
			 << "\n极差: " << range << "\t[" << min << ", " << max << "]" << endl;
	}
	return 0;
}

int TestN(double m0=72, double v0=6*6)			// 测试正态分布
{
	const int N=100000;
	double array[N]; 
				// 定义数组，即设置一个容量"足够的"的容器，用于存放一系列数据
	double mean, var, range, max, min;
				// 均值、方差、极差、最大值、最小值

	cout << "\n*** 正态分布（即高斯分布）N(μ, σ*σ)测试。其中均值μ="<< m0 << ", " << "方差σ*σ=" << v0 << endl;
	for(int n=10; n<=N; n*=10)
	{
		GetGaussData(array, n, m0, v0);			// 数组容器不一定用满
		mean = Mean(array, n);
		var = Variance(array, n);
		range = Range(array, n, max, min);
												// 第3、4两个参数必须是已经存在的变量
		cout << "\n数据规模 n = " << n
			 << "\n均值: " << mean
			 << "\n方差: " << var
			 << "\n极差: " << range << "\t[" << min << ", " << max << "]"
			 << "\n[μ-3σ, μ+3σ] = [" << mean-3*sqrt(var) << ", " << mean+3*sqrt(var) << "]" << endl;
	}
	return 0;
}

int main()
{
	srand(time(NULL));					// 设置随机数发生器的种子

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

double Mean(const double *array, int n)			// 计算均值
{
	double sum=0;
	for(int i=0; i<n; i++)
		sum += array[i];
	return sum/n;
}

double Variance(const double *array, int n)		// 计算方差
{					// 将计算方差的公式进一步化简
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
		t = array[i]-mean;		// 利用t减少计算量
		s += t*t;				// (array[i]-mean)*(array[i]-mean)
	}
	return s/n;
*/
}

double Range(const double *array, int n, double &max, double &min)	// 计算极差
{
	min = max = array[0];
	for(int i=1; i<n; i++)
	{
		if(array[i]<min) min = array[i];
		if(array[i]>max) max = array[i];
	}
	return max-min;
}
