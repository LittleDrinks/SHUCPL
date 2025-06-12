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
}

template <typename T> void Select(T *a, int size)	// ѡ������
{
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
		if (left >= right) continue;   // ���䳤��<=1��ֱ������

		// ���ѡ��pivot���������Ҷ�
		int id = UniformRand(left, right);
		T pivot = a[id];
		std::swap(a[id], a[right]);

		// ˫ָ��partition
		int i = left, j = right - 1;
		while (i <= j) {
			while (i <= j && a[i] <= pivot) ++i;
			while (i <= j && a[j] >= pivot) --j;
			if (i < j) std::swap(a[i], a[j]);
		}
		// ��pivot�ŵ���ȷ��λ��
		std::swap(a[i], a[right]);

		// ��벿��[left, i-1]  �Ұ벿��[i+1, right]
		stk.emplace(left, i - 1);
		stk.emplace(i + 1, right);
	}
}

#endif
