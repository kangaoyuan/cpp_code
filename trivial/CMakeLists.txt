cmake_minimum_required(VERSION 3.27)
set(CMAKE_CXX_STANDARD 17)
project(trivial LANGUAGES C CXX)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif()

add_executable(define define.cpp)
add_executable(sizeof sizeof.cpp)
add_executable(declavl declval.cpp)
add_executable(noexcept noexcept.cpp)
add_executable(overload overload.cpp)
add_executable(attribute attribute.cpp)
