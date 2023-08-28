cmake_minimum_required(VERSION 3.27)
set(CMAKE_CXX_STANDARD 17)
project(variadic LANGUAGES C CXX)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif()

add_executable(test _test_raw_variadic.cpp)
add_executable(raw_variadic raw_variadic.cpp)
add_executable(auto_variadic auto_variadic.cpp)
add_executable(SFINAE_variadic SFINAE_variadic.cpp)
add_executable(template_variadic template_variadic.cpp)
