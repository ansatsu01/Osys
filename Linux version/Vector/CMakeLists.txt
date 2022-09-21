cmake_minimum_required(VERSION 3.22)
project(Vector)

set(CMAKE_CXX_STANDARD 20)

add_library(Vector SHARED vector.cpp)

include_directories(../StaticLib)

find_library(ST_LIB libStaticLib.a ../StaticLib/cmake-build-debug)

target_link_libraries(${PROJECT_NAME} ${ST_LIB})