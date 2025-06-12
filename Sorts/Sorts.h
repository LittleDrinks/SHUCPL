// Sorts.h		三种（冒泡、选择、快速）基本排序算法（升序）
#ifndef SORTS_H
#define SORTS_H
#include <iostream>
#include <stack>
#include "MyRand.h"
using namespace std;

double gettime(int restart=0);

template <typename T> void GetMemory(T *&data, T *&data0, int n)	// 分配堆内存空间，通过参数"返回"首地址
{																	// 隐含约定：指针非空就表示指针"拥有"堆空间资源
	if(data0!=NULL) delete [] data0;								// 先释放原先所"拥有"的堆空间资源
	if(data !=NULL) delete [] data;
	data0 = new T[n];												// 重新申请新的（容量符合要求的）堆空间资源
	data = new T[n];
}

template <typename T> void FreeMemory(T *&data, T *&data0)			// 释放指针所"拥有"的堆空间资源
{
	if(data0!=NULL) delete [] data0;
	if(data !=NULL) delete [] data;
	data0 = data = NULL;											// 这一条赋值语句非常重要！保持"隐含约定"
}

template <typename T> void ReSet(T *data, const T *data0, int n)	// 用于恢复"原始数据"，以保证不同的排序算法处理完全相同的数据
{
	for(int i=0; i<n; i++)
		data[i] = data0[i];
}

template <typename T> bool Check(const T *a, int size)				// 仅检验数组元素是否满足升序（并未进行严格的正确性检查）
{
	for(int i=1; i<size; i++)
		if(a[i-1] > a[i])
			return false;
	return true;
}

// 三种基本的（没有优化的）排序算法
template <typename T> void Bubble(T *a, int size)	// 冒泡排序
{
	T temp;											// 定义一个局部变量，数据类型与形式数据类型相同
	int i, j;
	for(i=1; i<size; i++)							// 共进行 size-1 轮比较和交换
	{
		bool flag = true;
		for(j=0; j<size-i; j++)
		{
			if(a[j] > a[j+1])						// 相邻元素之间比较，必要时
			{
				flag = false;
				temp = a[j];						// 交换 a[j] 与 a[j+1]
				a[j] = a[j+1];
				a[j+1] = temp;
			}
		}
		if (flag) { break; }
	}
}

template <typename T> void Select(T *a, int size)	// 选择排序
{
	T temp;
	int i, j, k=0;
	for(i=1; i<size; i++)							// 循环size-1次
	{
		bool flag = false;
		for(j=i; j<size; j++)
			if(a[j] < a[k])
				k = j;								// 找出当前范围内"最小"元素的下标
		if(k!=i-1)									// 若"最小"元素不是a[i-1]，则交换之
		{
			temp = a[k];
			a[k] = a[i-1];
			a[i-1] = temp;
			flag = true;
		}
		k = i;
		if (!flag) {
			break;
		}
	}
}

template <typename T>
void Qsort(T *a, int size)
{
	using std::pair;
	using std::stack;

	stack<pair<int, int>> stk;
	stk.emplace(0, size - 1);

	while (!stk.empty()) {
		auto [left, right] = stk.top(); stk.pop();
		if (left >= right) continue;   // 区间长度<=1，直接跳过

		// 随机选择pivot，交换到右端
		int id = UniformRand(left, right);
		T pivot = a[id];
		std::swap(a[id], a[right]);

		// 双指针partition
		int i = left, j = right - 1;
		while (i <= j) {
			while (i <= j && a[i] <= pivot) ++i;
			while (i <= j && a[j] >= pivot) --j;
			if (i < j) std::swap(a[i], a[j]);
		}
		// 把pivot放到正确的位置
		std::swap(a[i], a[right]);

		// 左半部分[left, i-1]  右半部分[i+1, right]
		stk.emplace(left, i - 1);
		stk.emplace(i + 1, right);
	}
}

#endif
