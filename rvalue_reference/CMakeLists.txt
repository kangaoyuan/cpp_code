cmake_minimum_required(VERSION 3.27)
set(CMAKE_CXX_STANDARD 17)
project(rvalue LANGUAGES C CXX)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif()

add_executable(RAII RAII.cpp)
add_executable(raw_ptr raw_ptr.cpp)
add_executable(collapse collapse.cpp)
add_executable(shared_ptr shared_ptr.cpp)
add_executable(rvalue_ref rvalue_ref.cpp)
