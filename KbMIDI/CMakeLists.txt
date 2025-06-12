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