cmake_minimum_required(VERSION 3.24)
project(CppBfs)

set(CMAKE_CXX_STANDARD 17)

add_executable(CppBfs src/main.cpp src/bfs.h src/graph.h)
