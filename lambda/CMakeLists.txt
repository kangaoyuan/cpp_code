cmake_minimum_required(VERSION 3.27)
set(CMAKE_CXX_STANDARD 17)
project(any LANGUAGES C CXX)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif()


add_executable(test test_lambda.cpp)
add_executable(this this_lambda.cpp)
add_executable(constexpr constexpr_lambda.cpp)

