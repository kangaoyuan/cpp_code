cmake_minimum_required(VERSION 3.27)
project(inline LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif()

add_executable(test_static static_const.cpp)
add_executable(test_inline main.cpp test.cpp)
target_include_directories(test_inline PUBLIC .)
