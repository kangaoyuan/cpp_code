cmake_minimum_required(VERSION 3.27)
project(class_template LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif()

add_executable(enable_if enable_if.cpp)
add_executable(return_auto return_auto.cpp)
add_executable(if_constexpr if_constexpr.cpp)
add_executable(specialization specialization.cpp)
