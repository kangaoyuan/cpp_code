cmake_minimum_required(VERSION 3.27)
set(CMAKE_CXX_STANDARD 17)
project(constexpr LANGUAGES C CXX)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif()

add_executable(static_const static_const.cpp)
add_executable(ctor_constexpr ctor_constexpr.cpp)
add_executable(value_constexpr value_constexpr.cpp)
add_executable(example_constexpr example_constexpr.cpp)
