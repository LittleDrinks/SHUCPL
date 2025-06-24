// Sorts.h		���֣�ð�ݡ�ѡ�񡢿��٣����������㷨������
#ifndef SORTS_H
#define SORTS_H
#include <iostream>
#include <stack>
#include "MyRand.h"
using namespace std;

double gettime(int restart=0);

template <typename T> void GetMemory(T *&data, T *&data0, int n)	// ������ڴ�ռ䣬ͨ������"����"�׵�ַ
{																	// ����Լ����ָ��ǿվͱ�ʾָ��"ӵ��"�ѿռ���Դ
	if(data0!=NULL) delete [] data0;								// ���ͷ�ԭ����"ӵ��"�Ķѿռ���Դ
	if(data !=NULL) delete [] data;
	data0 = new T[n];												// ���������µģ���������Ҫ��ģ��ѿռ���Դ
	data = new T[n];
}

template <typename T> void FreeMemory(T *&data, T *&data0)			// �ͷ�ָ����"ӵ��"�Ķѿռ���Դ
{
	if(data0!=NULL) delete [] data0;
	if(data !=NULL) delete [] data;
	data0 = data = NULL;											// ��һ����ֵ���ǳ���Ҫ������"����Լ��"
}

template <typename T> void ReSet(T *data, const T *data0, int n)	// ���ڻָ�"ԭʼ����"���Ա�֤��ͬ�������㷨������ȫ��ͬ������
{
	for(int i=0; i<n; i++)
		data[i] = data0[i];
}

template <typename T> bool Check(const T *a, int size)				// ����������Ԫ���Ƿ��������򣨲�δ�����ϸ����ȷ�Լ�飩
{
	for(int i=1; i<size; i++)
		if(a[i-1] > a[i])
			return false;
	return true;
}

// ���ֻ����ģ�û���Ż��ģ������㷨
template <typename T> void Bubble(T *a, int size)	// ð������
{
	/*
	T temp;											// ����һ���ֲ�������������������ʽ����������ͬ
	int i, j;
	for(i=1; i<size; i++)							// ������ size-1 �ֱȽϺͽ���
	{
		bool flag = true;
		for(j=0; j<size-i; j++)
		{
			if(a[j] > a[j+1])						// ����Ԫ��֮��Ƚϣ���Ҫʱ
			{
				flag = false;
				temp = a[j];						// ���� a[j] �� a[j+1]
				a[j] = a[j+1];
				a[j+1] = temp;
			}
		}
		if (flag) { break; }
	}
	*/
    int lastSwap = size - 1;            // ��ʼ����󽻻�λ��Ϊ����ĩβ
    for (int i = 0; i < size - 1; i++)
    {
        bool swapped = false;         // ���ֽ�����־λ������Ƿ���������
        int currentSwap = -1;         // ��¼������󽻻�λ��
        // ����δ���򲿷֣�ֻ�������������󽻻�λ�ã�
        for (int j = 0; j < lastSwap; j++)
        {
            if (a[j] > a[j+1])
            {
                T temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
                swapped = true;      // ��Ƿ�������
                currentSwap = j;     // ���±�����󽻻�λ��
            }
        }
        if (!swapped) break;           // �������޽�����˵������ȫ����
        lastSwap = currentSwap;      // ������һ�ֵı����߽�
    }
}

template <typename T> void Select(T *a, int size)	// ѡ������
{
	/*
	T temp;
	int i, j, k=0;
	for(i=1; i<size; i++)							// ѭ��size-1��
	{
		bool flag = false;
		for(j=i; j<size; j++)
			if(a[j] < a[k])
				k = j;								// �ҳ���ǰ��Χ��"��С"Ԫ�ص��±�
		if(k!=i-1)									// ��"��С"Ԫ�ز���a[i-1]���򽻻�֮
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

template <typename T> void Qsort(T *a, int size)	// ��������
{
	/*
	T pivot, temp;
	int left=0, right=size-1;						// �±꣨������

	if(size<=1) return;

	pivot = a[right];								// ѡ�����һ��ֵΪ�ֽ�ֵ
	do
	{
		while(left<right && a[left]<=pivot) left++;	// �˴� "<=" ������ֽ�ֵ��ȵ�Ԫ����ʱ����ԭ��
		while(left<right && a[right]>=pivot)right--;// �˴� ">=" ������ֽ�ֵ��ȵ�Ԫ����ʱ����ԭ��
		if(left < right)
		{
			temp=a[left]; a[left]=a[right]; a[right]=temp;
		}
	}while(left < right);
	a[size-1] = a[left]; a[left] = pivot;			// �ҵ��ֽ�� left
	Qsort(a, left);									// �ݹ����(��ಿ��)
	Qsort(a+left+1, size-left-1);					// �ݹ����(�Ҳಿ��)
	*/

	// ʹ��ջ�洢������������飨��ʼָ��ͳ��ȣ�
	std::stack<std::pair<T*, int>> stack;
	stack.push(std::make_pair(a, size));

	while (!stack.empty()) {
		T* base = stack.top().first;
		int len = stack.top().second;
		stack.pop();

		if (len <= 1) continue;

		// ���ѡ���׼ֵ
		T pivot = base[std::rand() % len];
		int i = 0;    // ��ǰɨ��λ��
		int j = 0;    // С�ڻ�׼���ұ߽�
		int k = len;  // ���ڻ�׼����߽�

		// ��·���֣�С�� | ���� | ����
		while (i < k) {
			if (base[i] < pivot) {
				// ��С�ڻ�׼��Ԫ�ؽ�����ǰ��
				T temp = base[i];
				base[i] = base[j];
				base[j] = temp;
				++i;
				++j;
			} else if (pivot < base[i]) {
				// �����ڻ�׼��Ԫ�ؽ�������
				--k;
				T temp = base[i];
				base[i] = base[k];
				base[k] = temp;
			} else {
				// ���ڻ�׼��Ԫ�������м�
				++i;
			}
		}

		// ��ȡ�����鳤��
		int left_len = j;           // С�ڻ�׼�Ĳ���
		int right_len = len - k;    // ���ڻ�׼�Ĳ���

		// ����������ջ�����Һ����Ա�֤���������ȴ���
		if (right_len > 1) {
			stack.push(std::make_pair(base + k, right_len));
		}
		if (left_len > 1) {
			stack.push(std::make_pair(base, left_len));
		}
	}
}

#endif
