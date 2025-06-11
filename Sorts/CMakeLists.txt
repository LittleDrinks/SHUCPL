cmake_minimum_required(VERSION 3.31)
project(Sorts)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Sorts
        Main.cpp
        MyRand.cpp
        MyRand.h
        Score.cpp
        Score.h
        Sorts.h
        SortString.cpp)
