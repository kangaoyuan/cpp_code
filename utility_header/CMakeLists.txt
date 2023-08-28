cmake_minimum_required(VERSION 3.27)
set(CMAKE_CXX_STANDARD 17)
project(utility LANGUAGES C CXX)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif()

add_executable(output test_output.cpp)
