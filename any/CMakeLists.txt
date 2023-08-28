cmake_minimum_required(VERSION 3.27)
set(CMAKE_CXX_STANDARD 17)
project(any LANGUAGES C CXX)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif()

add_executable(usage_any usage_any.cpp)
add_executable(any_case event_source.hpp callback1.cpp callback2.cpp main.cpp)
