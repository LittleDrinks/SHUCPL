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
	/*
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
	*/
    int lastSwap = size - 1;            // 初始化最后交换位置为数组末尾
    for (int i = 0; i < size - 1; i++)
    {
        bool swapped = false;         // 本轮交换标志位（检测是否发生交换）
        int currentSwap = -1;         // 记录本轮最后交换位置
        // 遍历未排序部分（只需遍历到上轮最后交换位置）
        for (int j = 0; j < lastSwap; j++)
        {
            if (a[j] > a[j+1])
            {
                T temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
                swapped = true;      // 标记发生交换
                currentSwap = j;     // 更新本轮最后交换位置
            }
        }
        if (!swapped) break;           // 若本轮无交换，说明已完全有序
        lastSwap = currentSwap;      // 更新下一轮的遍历边界
    }
}

template <typename T> void Select(T *a, int size)	// 选择排序
{
	/*
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
	*/
	int minIndex=0, maxIndex=0;
	T temp;
	for (int i = 0, x = size - 1; i < size / 2; i++, x--)
	{
		minIndex = i;
		maxIndex = i;
		for (int j = i + 1; j <= x; j++)
		{
			if (a[j] < a[minIndex]) minIndex = j;
			if (a[j] > a[maxIndex]) maxIndex = j;
		}
		swap(a[i], a[minIndex]);
		// Update the maxIndex if necessary
		if (maxIndex == i)
		{
			maxIndex = minIndex;
		}
		swap(a[x], a[maxIndex]);
	}
}

template <typename T> void Qsort(T *a, int size)	// 快速排序
{
	/*
	T pivot, temp;
	int left=0, right=size-1;						// 下标（整数）

	if(size<=1) return;

	pivot = a[right];								// 选择最后一个值为分界值
	do
	{
		while(left<right && a[left]<=pivot) left++;	// 此处 "<=" 是让与分界值相等的元素暂时留在原地
		while(left<right && a[right]>=pivot)right--;// 此处 ">=" 是让与分界值相等的元素暂时留在原地
		if(left < right)
		{
			temp=a[left]; a[left]=a[right]; a[right]=temp;
		}
	}while(left < right);
	a[size-1] = a[left]; a[left] = pivot;			// 找到分界点 left
	Qsort(a, left);									// 递归调用(左侧部分)
	Qsort(a+left+1, size-left-1);					// 递归调用(右侧部分)
	*/

	// 使用栈存储待排序的子数组（起始指针和长度）
	std::stack<std::pair<T*, int>> stack;
	stack.push(std::make_pair(a, size));

	while (!stack.empty()) {
		T* base = stack.top().first;
		int len = stack.top().second;
		stack.pop();

		if (len <= 1) continue;

		// 随机选择基准值
		T pivot = base[std::rand() % len];
		int i = 0;    // 当前扫描位置
		int j = 0;    // 小于基准的右边界
		int k = len;  // 大于基准的左边界

		// 三路划分：小于 | 等于 | 大于
		while (i < k) {
			if (base[i] < pivot) {
				// 将小于基准的元素交换到前部
				T temp = base[i];
				base[i] = base[j];
				base[j] = temp;
				++i;
				++j;
			} else if (pivot < base[i]) {
				// 将大于基准的元素交换到后部
				--k;
				T temp = base[i];
				base[i] = base[k];
				base[k] = temp;
			} else {
				// 等于基准的元素留在中间
				++i;
			}
		}

		// 获取子数组长度
		int left_len = j;           // 小于基准的部分
		int right_len = len - k;    // 大于基准的部分

		// 将子数组入栈（先右后左以保证左子数组先处理）
		if (right_len > 1) {
			stack.push(std::make_pair(base + k, right_len));
		}
		if (left_len > 1) {
			stack.push(std::make_pair(base, left_len));
		}
	}
}

#endif
