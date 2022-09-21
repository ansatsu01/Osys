cmake_minimum_required(VERSION 3.22)
project(StaticLib)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-fPIC)
add_library(StaticLib library.cpp)
