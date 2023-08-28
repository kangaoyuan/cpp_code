cmake_minimum_required(VERSION 3.27)
set(CMAKE_CXX_STANDARD 17)
project(cmake_template LANGUAGES C CXX)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif()

add_executable(template_arg template_arg.cpp)
add_executable(auto_template_arg auto_template_arg.cpp)
add_executable(data_member_pointer data_member_pointer.cpp)
add_executable(partial_specialization partial_specialization.cpp)
