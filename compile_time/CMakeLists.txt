cmake_minimum_required(VERSION 3.27)
set(CMAKE_CXX_STANDARD 17)
project(compile LANGUAGES C CXX)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif()

add_executable(fmap fmap.cpp)
add_executable(compile_time compile_time.cpp)
add_executable(if_deduction If_deduction.cpp)
add_executable(while_deduction While_deduction.cpp)


