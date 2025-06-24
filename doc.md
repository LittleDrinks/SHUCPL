本文件为【2024-2025夏季学期《计算机编程实训》（0830A034）课程】作业操作文档

# 前置工作



*实测在 vscode 中 `Sorts\SortString.cpp` 会报错，本文档使用 Clion，以避免可能的环境问题，不要在乎下发的 `MakePrj`，请相信 Clion 比它好用一万倍*



- [ ] 安装CMake，并使用 `cmake --version` 验证安装
- [ ] 将 g++ 添加至环境变量
- [ ] 安装 Clion（可参考 [CLion安装、配置、使用、调试（完全小白向）](https://blog.csdn.net/annesede/article/details/133940779) ）
- [ ] 从学习通中下载所有的代码文件（`Sorts`、`kbMIDI`、`SortShow排序秀`、`SortShow排序秀(NEW)`）
- [ ] 使用 Clion 打开任意一个文件夹，如果出现文件编码问题，选择 GBK 后重新加载



## 配置 Sorts 相关环境



-   [ ] 打开 `Sorts`文件夹，在任务栏点击“工具——CMake——创建 CMakeLists.txt”配置 CMakeList，选中所有 `*.h*` 和`*.cpp*`文件，在上方任务栏点击运行，看到正确的输出（如果这一步没能成功，请选择“工具——CMake——卸载 CMake 项目重新进行”后重复上述步骤）
-   [ ] 在 `cmake-build-debug` 目录下确认 `Sorts.exe`，将下发文件中的 `Release` 目录下的文件复制到与 `Sorts.exe` 同目录，在这个目录下运行命令行，并执行 `run.bat`



```
数据类型: i (正态分布)
        冒泡排序        选择排序        快速排序
1024    0.003   0.001   0       冒泡排序: 正确  选择排序: 正确  快速排序: 正确
2048    0.004   0.002   0       冒泡排序: 正确  选择排序: 正确  快速排序: 正确
4096    0.028   0.006   0.001   冒泡排序: 正确  选择排序: 正确  快速排序: 正确
8192    0.061   0.029   0.002   冒泡排序: 正确  选择排序: 正确  快速排序: 正确
16384   0.361   0.096   0.004   冒泡排序: 正确  选择排序: 正确  快速排序: 正确
```



*如果运行失败，请尝试去除路径中的中文*

如果遇到栈溢出问题（`exit code -1073741571 (0xC00000FD)`），可以暂时将 `Main.cpp` 第 47 行的 $n$ 设为 `8192`。如果您想知道为什么，请自行搜索递归与系统栈的关系。



## 配置 MIDI 相关环境



在开始前，请确保您知道 mingw64 文件夹在电脑上的位置，否则请参考[这篇](https://zhuanlan.zhihu.com/p/643934671)在[这里](https://github.com/niXman/mingw-builds-binaries/releases)下载高版本 g++ 编译器，并将其存放在一个简单的目录下，如 `D:\\`

*参考[clion使用winmm.lib库文件（在MinGW中是libwinmm.a） ](https://www.cnblogs.com/21MINM/p/16871809.html)进行配置*



-   [ ] 打开 `kbMIDI`文件夹，在任务栏点击“工具——CMake——创建 CMakeLists.txt”配置 CMakeList，选中所有 `*.h*` 和`*.cpp*`文件
-   [ ] 对照下方的 `CMakeLists.txt` 添加命令，确保编译时可以链接到 winmm.lib

*或在编译命令中添加 `-lwinmm` 参数*



```cmake
cmake_minimum_required(VERSION 3.31)
project(KbMIDI)

set(CMAKE_CXX_STANDARD 14)
include_directories(D:\\mingw64\\include) # 添加这一句
link_directories(D:\\mingw64\\lib) # 添加这一句
link_directories(winmm) # 添加这一句

include_directories(.)

add_executable(KbMIDI
        KbMIDI.cpp
        KbMIDI.h
        KbMusic.cpp)

target_link_libraries(KbMIDI winmm) # 添加这一句
```



-   [ ] 点击任务栏的运行，在 `cmake-build-debug` 目录下找到 `.exe` 文件，直接双击运行确认编译成功
-   在任务栏“运行——编辑配置”中勾选在外部控制台运行，以达到更好的显示效果




-   [ ] 打开 `SortShow排序秀` 完成类似的配置工作



# 排序算法的实验与优化



在这一部分，您需要：



1.   学习【冒泡排序】、【选择排序】、【快速排序】三种排序算法
2.   对于每种排序算法，您需要完成“基本介绍”、“未优化的代码”、“数据分析（表格+柱状图）”、“优化后的代码”、“优化前后效果比较（表格+柱状图）”五个部分
3.   完成多种排序算法的联合测试



需要使用的代码均存放于 `Sorts` 文件夹下，项目的逻辑如下：



-   `MyRand.h / MyRand.cpp` 提供了随机数据生成辅助，便于测试不同规模和分布的数据排序效果。
-   `Main.cpp` 是程序的主入口，对各种排序算法进行适应性和用时测试。
    -   调用 `Test((int)(0))` 进行 `int` 类型的测试
    -   调用 `Test((double)(0))` 进行 `double` 类型的测试
    -   `Score.h / Score.cpp` 自定义了一个结构体类型，调用其中的 `TestScore()` 进行排序测试。
    -   `SortString.h / SortString.cpp` 用不同的方式存储字符串，分别调用其中的两个 `Bubble` 函数进行排序测试
-   `Release` 和 `Debug` 两个目录下分别存放了 `run.bat`，用于运行编译所得的 `Sorts.exe`，并按给定的格式输出到文件（详见 `results_xxx.txt`），再使用 `open.bat` 在 excel 中显示数据



在整个项目的编写过程中，您只需要修改 `Main.cpp` 中的三个排序函数以及 `SortString.cpp` 中的两个 `Bubble` 函数



-   您已经在前置工作中完成了代码环境的配置
- [ ] 学习【冒泡排序】、【选择排序】、【快速排序】三种排序算法的基本逻辑，看懂优化前的代码



您可能会产生的疑惑：



-   [快排](https://oi-wiki.org/basic/quick-sort/)
-   `template` 的用法
-   各种指针
-   多文件的编译、链接逻辑



- [ ] 测试三种排序算法



使用 Clion 编译后会在目录下产生一个 `cmake-build-debug` 目录，里面有一个 `Sorts.exe`，将下发的 Release 文件夹中 `run.bat` 等文件拷贝到 `Sorts.exe` 同目录下，在同目录的命令行中运行 `run.bat`，等待运行完成后打开 `results.xlsx` 和 `results_release.txt`，选中 `results.xlsx` 中左上角的单元格，将 `results_release.txt` 中的内容复制到 `xlsx` 中，图表会对应更新。

*`Debug` 和 `Release` 目录下提供的 `run.bat` 仅有文件名和提示语的不同。*



- [ ] 尝试优化三种排序算法



可能的优化思路：

-   手写栈代替系统栈防止溢出
-   复杂度优化：
    -   使用随机数、三数取中等方式防止快排退化

-   常数优化：
    -   在数据有序时直接退出
    -   减少无用的交换、判断、循环
    -   采用多种排序算法混合缩小常数




[参考资料：oi-wiki 快速排序](https://oi-wiki.org/basic/quick-sort/)



# 舞动的排序



在这一部分，您需要：



1.   看懂项目结构和逻辑
2.   看懂至少一个排序可视化的源码
3.   修改项目中对应的位置，将您的排序算法可视化展示



需要的所有代码均存放于 `SortShow排序秀` 文件夹下，项目的逻辑如下：



-   `main.cpp` 中实现了排序可视化的主界面
    -   通过 `conio.h` 中的 `getch()` 函数获取输入字符
    -   在 `switch()` 中控制排序可视化的入口
    -   每个排序算法均通过 `Start()` 和 `Finish()` 完成初始化显示
-   `Sort_Show.cpp` 中实现了若干可视化版本的排序算法
    -   所有排序算法均需传入两个参数 `*array` 和 `length`，表示数组的头指针和长度
-   `SortShow.h` 头文件定义了可视化所需的各种函数
    -   `ShowText(x, y, bkcolor, color, str)` 可以在控制台 $(x,y)$ 坐标处显示背景色为 `bkcolor`，字体颜色为 `color` 的字符串 `str`，所有下发的示例代码均取 `bkcolor=0`，`color=15`。将 `str` 设为空格可以覆盖之前在此位置上显示的若干个字符。
    -   调用 `SWAP(array, idx1, idx2)` 以交换 `array` 中下标为 `idx1` 和 `idx2` 的两项，并进行对应的可视化显示
    -   调用 `ShowBars(x1, y1, val1, x2, y2, val2)` 在 $(x_1,y_1)$ 和 $(x_2, y_2)$ 处分别闪烁并显示两根长度为 $val_1$ 和 $val_2$ 的柱形图
    -   以上若干函数中的坐标均有对应的变量 `col1`、`top` 控制，请参考下发代码中原本的实现进行指定



在整个项目的编写中，您需要修改 `Main.cpp` 中的界面显示、`switch()` 下的函数调用，并在 `Sort_show.cpp` 中实现可视化版本的排序算法。

在这里，您并不需要掌握 MIDI 数字接口的编写，只需要调用实现好的 `SWAP`、`ShowText()`、`ShowBars()` 函数就可以完成可视化的工作。



- [ ] 看懂 `Sorts_Show.cpp` 中至少一个排序算法可视化的实现



您可能遇到的问题：



-   通过在 `ShowText()` 函数中传入 `x=col1-k` 在左侧手动显示提示词或过程量，注意根据现实的字符长度修改 `k` 
-   `ShowText()` 中 `Str` 传入的空格数不够导致原有的文字未被完全覆盖



- [ ] 针对优化后的一个排序算法，实现可视化实现



*本人仿照下发代码实现的插入排序可视化，作为参考*

```cpp
// Sort_Show.cpp
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

// Main.cpp
const char *str[]={	"1 ---- 重新生成原始数据(D)",
                   "2 ---- 冒泡排序........(B)",
                   "3 ---- 选择排序........(S)",
                   "4 ---- 归并排序........(M)",
                   "5 ---- 快速排序........(Q)",
                   "6 ---- 插入排序........(I)",  // 添加这一行，主界面上的提示词
                   "0 ---- 退出..........(ESC)",
                   "请选择: "};

// Main.cpp
switch(choice)
{
    // 添加以下几行    
    case '6':
    case 'i':
    case 'I':	col1 = 40;
        		SetConsoleTitle("插入排序（Insertion Sorting）");
        		Start();
       			Insert_Sort(array, N);
        		Finish();
}
```



# MIDI 实现优化算法可视化及设计歌曲


在这一部分，您需要：

1. 了解一些基本的乐理知识，了解最基本的 MIDI 接口
2. *学习多线程、`clock()` 等 c++ 特性，学习 MIDI editor，学习 mid 文件，以更好地完成您的任务*
3. 解决 `习题课\习题课3\MIDIexample\MIDIexample.cpp` 中提到的若干问题
4. 上网找一首您喜欢的音乐的乐谱，根据您编写的代码将其播放出来



关于基本的 MIDI 接口，您需要知道:

```cpp
// 打开 MIDI
HMIDIOUT handle;
midiOutOpen(&handle, 0, 0, 0, CALLBACK_NULL);

// 发音
DWORD dwMessage = (iVolume << 16) | (iFlip << 8) | iStatus        | iChannel;
//      音量      |     音符     | 状态字节(高4位) | 通道(低4位)
midiOutShortMsg(handle, dwMessage);

// 关闭 MIDI
midiOutClose(handle);
```

关于乐理知识，您需要知道：上述 MIDI 代码中的音量、音符、状态字节、通道代表了什么？有哪些可用的参数？

上述提到的参数中最重要的是音符。您需要知道：可以通过 `((isSharp? C_Scale_s[lvl][x]: C_Scale[lvl][x]) << 8)` 调用如下定义的变量，以控制音高（`lvl`），音调（`x`）和是否升半音（`isSharp`）

```cpp
enum scale{
    Rest=0,
    C8=108,
    B7=107,A7s=106,A7=105,G7s=104,G7=103,F7s=102,F7=101,E7=100,D7s=99, D7=98, C7s=97, C7=96,
    B6=95, A6s=94, A6=93, G6s=92, G6=91, F6s=90, F6=89, E6=88, D6s=87, D6=86, C6s=85, C6=84,
    B5=83, A5s=82, A5=81, G5s=80, G5=79, F5s=78, F5=77, E5=76, D5s=75, D5=74, C5s=73, C5=72,
    B4=71, A4s=70, A4=69, G4s=68, G4=67, F4s=66, F4=65, E4=64, D4s=63, D4=62, C4s=61, C4=60,
    B3=59, A3s=58, A3=57, G3s=56, G3=55, F3s=54, F3=53, E3=52, D3s=51, D3=50, C3s=49, C3=48,
    B2=47, A2s=46, A2=45, G2s=44, G2=43, F2s=42, F2=41, E2=40, D2s=39, D2=38, C2s=37, C2=36,
    B1=35, A1s=34, A1=33, G1s=32, G1=31, F1s=30, F1=29, E1=28, D1s=27, D1=26, C1s=25, C1=24,
    B0=23, A0s=22, A0=21
};
const int C_Scale[7][7]={{C1,D1,E1,F1,G1,A1,B1},
                            {C2,D2,E2,F2,G2,A2,B2},
                            {C3,D3,E3,F3,G3,A3,B3},
                            {C4,D4,E4,F4,G4,A4,B4},
                            {C5,D5,E5,F5,G5,A5,B5},
                            {C6,D6,E6,F6,G6,A6,B6},
                            {C7,D7,E7,F7,G7,A7,B7}};
const int C_Scale_s[7][7]={{C1s,D1s,-1,F1s,G1s,A1s,-1},
                            {C2s,D2s,-1,F2s,G2s,A2s,-1},
                            {C3s,D3s,-1,F3s,G3s,A3s,-1},
                            {C4s,D4s,-1,F4s,G4s,A4s,-1},
                            {C5s,D5s,-1,F5s,G5s,A5s,-1},
                            {C6s,D6s,-1,F6s,G6s,A6s,-1},
                            {C7s,D7s,-1,F7s,G7s,A7s,-1}};
```

可能的多音轨优化思路：

1. 使用多线程同步播放两条音轨
2. 调用 `clock()` 查询音符播放时长，如果该节拍未结束，则一直等待

有用的链接：

- [C++演奏《起风了》的代码](https://www.bilibili.com/opus/775532688542007328)
- [C++ 也能照着乐谱弹钢琴？让你的代码有 bgm 伴奏！](https://www.bilibili.com/video/BV1DH4y117ga/?share_source=copy_web&vd_source=6bdc78c36edc3731774f242dd88cfa5b)，后半部分代码截自本项目，鸣谢
- [找乐谱](https://www.everyonepiano.cn/Music.html)

