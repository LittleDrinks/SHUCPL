

本文件为【2024-2025夏季学期《计算机编程实训》（0830A034）课程】作业操作文档

# 前置工作



*实测在 vscode 中 `Sorts\SortString.cpp` 会报错，本文档使用 Clion，以避免可能的环境问题，不要在乎下发的 `MakePrj`，请相信 Clion 比它好用一万倍*



-   [ ] 安装CMake，并使用 `cmake --version` 验证安装
-   [ ] 安装 Clion（可参考 [CLion安装、配置、使用、调试（完全小白向）](https://blog.csdn.net/annesede/article/details/133940779) ）
-   [ ] 从学习通中下载所有的代码文件（`Sorts`、`kbMIDI`、`SortShow排序秀`、`SortShow排序秀(NEW)`）
-   [ ] 使用 Clion 打开任意一个文件夹，如果出现文件编码问题，选择 GBK 后重新加载



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



如果遇到栈溢出问题（`exit code -1073741571 (0xC00000FD)`），可以暂时将 `Main.cpp` 第 47 行的 $n$ 设为 `8192`



## 配置 MIDI 相关环境



在开始前，请确保您知道 mingw64 文件夹在电脑上的位置，否则请参考[这篇](https://zhuanlan.zhihu.com/p/643934671)在[这里](https://github.com/niXman/mingw-builds-binaries/releases)下载高版本 g++ 编译器，并将其存放在一个简单的目录下，如 `D:\\`

*参考[clion使用winmm.lib库文件（在MinGW中是libwinmm.a） ](https://www.cnblogs.com/21MINM/p/16871809.html)进行配置*



-   [ ] 打开 `kbMIDI`文件夹，在任务栏点击“工具——CMake——创建 CMakeLists.txt”配置 CMakeList，选中所有 `*.h*` 和`*.cpp*`文件
-   [ ] 对照下方的 `CMakeLists.txt` 添加命令，确保编译时可以链接到 winmm.lib



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


-   [ ] 打开 `SortShow排序秀` 完成类似的配置工作



# 排序算法的实验与优化



在这一部分，您需要：



1.   学习【冒泡排序】、【选择排序】、【快速排序】三种排序算法
2.   对于每种排序算法，您需要完成“基本介绍”、“未优化的代码”、“数据分析（表格+柱状图）”、“优化后的代码”、“优化前后效果比较（表格+柱状图）”五个部分



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



使用 Clion 编译后会在目录下产生一个 `cmake-build-debug` 目录，里面有一个 `Sorts.exe`，将下发的 Release 文件夹中 `run.bat` 等文件拷贝到 `Sorts.exe` 同目录下，在命令行中运行 `run.bat`，等待运行完成后打开 `results.xlsx` 和 `results_release.txt`，选中 `results.xlsx` 中左上角的单元格，将 `results_release.txt` 中的内容复制到 `xlsx` 中，图表会对应更新。

*`Debug` 和 `Release` 目录下提供的 `run.bat` 仅有文件名和提示词的不同。*



- [ ] 尝试优化三种排序算法



可能的优化思路：

-   在数据有序时直接退出
-   减少无用的交换、判断、循环
-   手写栈代替系统栈防止溢出
-   使用随机数、三数取中等方式防止快排退化
-   采用多种排序算法混合缩小常数



# MIDI 实现优化算法可视化及设计歌曲





# 舞动的排序

