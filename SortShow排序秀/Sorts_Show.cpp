// Sorts_Show.cpp	具体的排序算法成员函数定义（相应的函数声明在文件SortShow.h中）
#include "SortShow.h"
#include <conio.h>
#include <stack>

void Bubble_Sort(int *array, int length)
{
	ShowText(col1-4, top-1, 0, 15, "︻");
	ShowText(col1-4, top+length, 0, 15, "︼");
	for(int i=1; i<length; i++)
	{
		for(int j=0; j<length-i; j++)
		{
			if(array[j] > array[j+1])		// 有元素需要交换时
				SWAP(array, j, j+1);
			else							// 无元素需要交换时，展示曾比较过
				ShowBars(col1, top+j, array[j], col1, top+j+1, array[j+1]);
		}
		ShowText(col1-4, top+length-i+1, 0, 15, "  ");
		ShowText(col1-4, top+length-i, 0, 15, "︼");
	}
	ShowText(col1-4, top+1, 0, 15, "  ");
	ShowText(col1-4, top-1, 0, 15, "  ");
}

void Select_Sort(int *array, int length)	// 选择排序
{
	int k;
	
	ShowText(col1-4, top+length, 0, 15, "︼ ");
	for(int i=0; i<length-1; i++)
	{
		k = i;
		ShowText(col1-4, top+i-1, 0, 15, "︻");
		ShowText(col1-4, top+i, 0, 15, "min");
		for(int j=i+1; j<length; j++)
		{
			ShowBars(col1, top+j, array[j], col1, top+k, array[k]);
			if(array[j] < array[k])
			{
				ShowText(col1-4, top+k, 0, 15, "   ");
				k = j;
				ShowText(col1-4, top+k, 0, 15, "min");
			}
		}
		if(k!=i)
			SWAP(array, k, i);
		ShowText(col1-4, top+k, 0, 15, "   ");
		ShowText(col1-4, top+i-1, 0, 15, "   ");
	}
	ShowText(col1-4, top+length, 0, 15, "   ");
}

void Insert_Sort(int *array, int length) {
	for (int i = 1; i < length; i++) {
		int k = i;
		ShowText(col1-4, top+i, 0, 15, "NOW");
		for (int j = 0; j < i; j++) {
			ShowText(col1-8, top+j, 0, 15, "INS");
			if (array[j] > array[i]) {
				k = j; break;
			} else {
				ShowBars(col1, top+j, array[j], col1, top+i, array[i]);
			}
			ShowText(col1-8, top+j, 0, 15, "   ");
		}
		for (int j = i; j > k; --j) {
			SWAP(array, j, j-1);
		}
		ShowText(col1-8, top+k, 0, 15, "   ");
		ShowText(col1-4, top+i, 0, 15, "   ");
	}
}

void Merge_Sort(int *a, int size)
{
	int r = 2;
	if(size<=1)
		return;
	if(size==2)
	{
		if(a[0] > a[1])
			SWAP(a, 0, 1);
		else
			ShowBars(col1, top+a-array, a[0], col1, top+a-array+1, a[1]);
		return;
	}
	int i=0, j=0, k=0, len1=size/2, len2=size-size/2;
	int *b=a+len1;
	Merge_Sort(a, len1);
	Merge_Sort(b, len2);

	ShowText(col1-3, top+a-array, 0, 15, "︻");
	ShowText(col1-3, top+b-array, 0, 15, "—");
	ShowText(col1-3, top+b-array+len2, 0, 15, "︼");

	for(i=0; i<len1; i++)
	{
		MoveBar(col1, a-array+i+top, r*a[i], col2, i+top);
		temp[i] = a[i];
	}
	getch();

	i = j = k = 0;
	for(i=j=0; i<len1 && j<len2; k++)
	{
		if(temp[i]<=b[j])
		{
			MoveBar(col2, i+top, r*temp[i], col1, a-array+k+top);
			a[k] = temp[i++];
		}
		else
		{
			MoveBar(col1, b-array+j+top, r*b[j], col1, a-array+k+top);
			a[k] = b[j++];
		}
		getch();
	}
	while(i<len1)
	{
		MoveBar(col2, i+top, r*temp[i], col1, a-array+k+top);
		a[k++] = temp[i++];
	}
	while(j<len2)
	{
		MoveBar(col1, b-array+j+top, r*b[j], col1, a-array+k+top);
		a[k++] = b[j++];
	}
	ShowText(col1-3, top+a-array, 0, 15, "  ");
	ShowText(col1-3, top+b-array, 0, 15, "  ");
	ShowText(col1-3, top+b-array+len2, 0, 15, "  ");
}

/*
void Quick_Sort(int *a, int size)
{
	char lStr[]="{[(<abcdefghijkl", rStr[]="}])>ABCDEFGHIJKL";	// 展示递归过程中的"层次"
	int left=0, right=size-1;
	int pivot = a[right];			// 以右端的值为轴（值）
	static int layer=-1;			// 局部静态变量，记录递归的层数

	layer++;
	if(size<=1)
	{
		layer--;
		return ;
	}
	ShowChar(col1-6-2*layer, top+a-array, 0, 15, lStr[layer]);
	ShowChar(col1-6-2*layer, top+a-array+size-1, 0, 15, rStr[layer]);
	ShowText(col1-2, top+a-array+size-1, 0, 15, "*");
	if(size==2)
	{
		if(a[0] > a[1])
		{
			SWAP(a, 0, 1);
		}
		ShowText(col1-2, top+a-array+size-1, 0, 15, " ");
		layer--;
		return;
	}
	do
	{
		ShowText(col1-4, top+a-array+left, 0, 15, "L");
		ShowText(col1-3, top+a-array+right, 0, 15, "R");
		while(left < right && (a[left] <= pivot))
		{
			ShowBars(col1, top+a-array+left, a[left], col1, top+a-array+size-1, pivot);
			left++;						// 找到左侧严格大于轴值的元素（下标）
			ShowText(col1-4, top+a-array+left-1, 0, 15, " ");
			ShowText(col1-4, top+a-array+left, 0, 15, "L");
		}
		while(left < right && (pivot <= a[right]))
		{
			ShowBars(col1, top+a-array+right, a[right], col1, top+a-array+size-1, pivot);
			right--;					// 找到右侧严格小于轴值的元素（下标）
			ShowText(col1-3, top+a-array+right+1, 0, 15, " ");
			ShowText(col1-3, top+a-array+right, 0, 15, "R");
		}
		if(left < right)
		{
			SWAP(a, left, right);
		}
	}while(left < right);
	SWAP(a, left, size-1);				// 至此，left以左全不超过轴值，left到位，left以右全部小于轴值
	ShowText(col1-1, top+a-array+left, 0, 15, "-");
	ShowText(col1-4, top+a-array+left, 0, 15, " ");
	ShowText(col1-3, top+a-array+right, 0, 15, " ");

	ShowText(col1-2, top+a-array+size-1, 0, 15, " ");

	Quick_Sort(a, left);				// 递归处理a[0],...,a[left-1]（长度left）
	ShowText(col1-1, top+a-array+left, 0, 15, " ");
	Quick_Sort(a+left+1, size-left-1);	// 递归处理a[left+1],...,a[size-1]（长度size-left-1）
	layer--;
}
*/

char lStr[] = "{[(<abcdefghijkl";
char rStr[] = "}])>ABCDEFGHIJKL";

void Quick_Sort(int *a, int size)
{
    if (size <= 1) return;

    struct StackItem {
        int *base;
        int len;
        int offset;
        int depth;
        int pivotIndex;
    };

    std::stack<StackItem> stack;
    stack.push({a, size, static_cast<int>(a - array), 0, 0});

    int maxDepth = sizeof(lStr) - 1;

    while (!stack.empty()) {
        int *base = stack.top().base;
        int len = stack.top().len;
        int offset = stack.top().offset;
        int depth = stack.top().depth;
        int pivotIndex = stack.top().pivotIndex;
        stack.pop();

        if (len <= 1) continue;

        // 显示当前递归层级的括号
        char lChar = (depth < maxDepth) ? lStr[depth] : lStr[maxDepth-1];
        char rChar = (depth < maxDepth) ? rStr[depth] : rStr[maxDepth-1];
        ShowChar(col1-6-2*depth, top+offset, 0, 15, lChar);
        ShowChar(col1-6-2*depth, top+offset+len-1, 0, 15, rChar);

        // 随机选择基准值位置
        if (pivotIndex == 0) {
            pivotIndex = std::rand() % len;
        }
        int pivot = base[pivotIndex];

        // 在基准值实际位置显示标记
        ShowText(col1-2, top+offset+pivotIndex, 0, 15, "*");
        int lastPivotPos = pivotIndex;

        int i = 0;
        int j = 0;
        int k = len;

        // 显示初始指针位置
        ShowText(col1-4, top+offset+i, 0, 15, "I");
        ShowText(col1-5, top+offset+j, 0, 15, "J");
        if (k < len) {
            ShowText(col1-3, top+offset+k, 0, 15, "K");
        }

        // 跟踪基准值位置的变化
        int currentPivotPos = pivotIndex;

        while (i < k) {
            // 清除旧位置的基准值标记（如果位置变化）
            if (currentPivotPos != lastPivotPos) {
                ShowText(col1-2, top+offset+lastPivotPos, 0, 15, " ");
                lastPivotPos = currentPivotPos;
            }

            // 高亮当前元素和基准值
            ShowBars(col1, top+offset+i, base[i],
                     col1, top+offset+currentPivotPos, pivot);
            ShowText(col1-4, top+offset+i, 0, 10, "I");

            if (base[i] < pivot) {
                SWAP(base, i, j);

            	// 清除旧位置的基准值标记
            	if (i == currentPivotPos || j == currentPivotPos) {
            		ShowText(col1-2, top+offset+currentPivotPos, 0, 15, " ");
            	}

            	// 交换前检查基准值位置
            	if (i == currentPivotPos) currentPivotPos = j;
            	else if (j == currentPivotPos) currentPivotPos = i;

                // 在新位置显示基准值标记
                ShowText(col1-2, top+offset+currentPivotPos, 0, 15, "*");
                lastPivotPos = currentPivotPos;

                // 更新指针显示
            	ShowText(col1-5, top+offset+j, 0, 15, " ");
            	ShowText(col1-4, top+offset+i, 0, 15, " ");
            	i++;
            	j++;

                // 显示新位置的I指针
                if (i < len) {
                    ShowText(col1-4, top+offset+i, 0, 10, "I");
                }
                ShowText(col1-5, top+offset+j, 0, 14, "J");
            } else if (base[i] > pivot) {
                k--;

            	SWAP(base, i, k);

            	// 清除旧位置的基准值标记
            	if (i == currentPivotPos || k == currentPivotPos) {
            		ShowText(col1-2, top+offset+currentPivotPos, 0, 15, " ");
            	}

            	// 交换前检查基准值位置
            	if (i == currentPivotPos) currentPivotPos = k;
            	else if (k == currentPivotPos) currentPivotPos = i;

                // 在新位置显示基准值标记
                ShowText(col1-2, top+offset+currentPivotPos, 0, 15, "*");
                lastPivotPos = currentPivotPos;

                // 更新K指针显示
                if (k < len - 1) {
                    ShowText(col1-3, top+offset+k+1, 0, 15, " ");
                }
                ShowText(col1-3, top+offset+k, 0, 12, "K");

                // 重新显示I指针（位置不变）
                ShowText(col1-4, top+offset+i, 0, 10, "I");
            } else {
                // 清除I指针旧位置标记
                ShowText(col1-4, top+offset+i, 0, 15, " ");

            	// 清除I指针旧位置标记
            	ShowText(col1-4, top+offset+i, 0, 15, " ");
                i++;

                if (i < len) {
                    // 显示新位置的I指针
                    ShowText(col1-4, top+offset+i, 0, 10, "I");
                }
            }
        }

        // 清除指针标记（确保在范围内）
        if (i < len) ShowText(col1-4, top+offset+i, 0, 15, " ");
        if (j < len) ShowText(col1-5, top+offset+j, 0, 15, " ");
        if (k < len) ShowText(col1-3, top+offset+k, 0, 15, " ");

        // 清除基准值标记
        if (currentPivotPos < len) {
            ShowText(col1-2, top+offset+currentPivotPos, 0, 15, " ");
        }

        // 清除当前层括号
        ShowChar(col1-6-2*depth, top+offset, 0, 15, ' ');
        ShowChar(col1-6-2*depth, top+offset+len-1, 0, 15, ' ');

        // 准备子数组
        int left_len = j;
        int right_len = len - k;
        int right_offset = offset + k;

        // 压入子数组
        if (right_len > 1) {
            stack.push({base + k, right_len, right_offset, depth + 1, 0});
        }
        if (left_len > 1) {
            stack.push({base, left_len, offset, depth + 1, 0});
        }
    }
}