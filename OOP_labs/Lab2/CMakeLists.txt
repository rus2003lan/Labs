cmake_minimum_required(VERSION 3.22)
project(Lab2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Lab2
        arc_spiral.cpp
        arc_spiral.hpp
        main.cpp)
