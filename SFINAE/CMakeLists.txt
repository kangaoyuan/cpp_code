cmake_minimum_required(VERSION 3.27)
set(CMAKE_CXX_STANDARD 17)
project(SFINAE LANGUAGES C CXX)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif()

include_directories(.)

add_executable(raw_SFINAE raw_SFINAE.cpp)
add_executable(decltype_SFINAE decltype_SFINAE.cpp)
add_executable(enable_if_SFINAE enable_if_SFINAE.cpp)
add_executable(tag_dispatch_SFINAE tag_dispatch_SFINAE.cpp)
