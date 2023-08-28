cmake_minimum_required(VERSION 3.27)
set(CMAKE_CXX_STANDARD 17)
project(example LANGUAGES C CXX)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif()

add_executable(example1 example1.cpp)
add_executable(example2 example2.cpp)
add_executable(example template.hpp example.cpp)

