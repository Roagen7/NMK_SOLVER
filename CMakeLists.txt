cmake_minimum_required(VERSION 3.21)
project(ASD_NMK)

set(CMAKE_CXX_STANDARD 14)

add_executable(ASD_NMK main.cpp Board.cpp Board.h solve.h solve.cpp)
