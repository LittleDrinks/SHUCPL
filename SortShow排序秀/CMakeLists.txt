cmake_minimum_required(VERSION 3.31)
project(SortShow)

set(CMAKE_CXX_STANDARD 14)
include_directories(D:\\mingw64\\include) # 添加这一句
link_directories(D:\\mingw64\\lib) # 添加这一句
link_directories(winmm) # 添加这一句

include_directories(.)

add_executable(SortShow
        Main.cpp
        Sorts_Show.cpp
        SortShow.cpp
        SortShow.h)

target_link_libraries(SortShow winmm) # 添加这一句