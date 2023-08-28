cmake_minimum_required(VERSION 3.27)
set(CMAKE_CXX_STANDARD 17)
project(thread LANGUAGES C CXX)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif()

add_executable(nojoin_bug nojoin_bug.cpp)
add_executable(thrad_case thread_case.cpp)
add_executable(deadlock_bug deadlock_bug.cpp)
add_executable(async_resolution async_resolution.cpp)
add_executable(synchronization_bug synchronization_bug.cpp)
add_executable(detach_resolution detach_resolution.cpp)
