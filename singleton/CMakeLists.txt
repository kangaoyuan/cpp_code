cmake_minimum_required(VERSION 3.27)
set(CMAKE_CXX_STANDARD 17)
project(singleton LANGUAGES C CXX)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif()

find_package(spdlog REQUIRED)

add_executable(test_atomic_singleton test_atomic_singleton.cpp atomic_singleton.cpp)
add_executable(test_pthread_singleton test_pthread_singleton.cpp pthread_singleton.cpp)
add_executable(test_local_static_singleton test_local_static_singleton.cpp local_static_singleton.cpp)
target_link_libraries(test_atomic_singleton spdlog::spdlog)
target_link_libraries(test_pthread_singleton spdlog::spdlog)

# target_include_directories(XXX_executable PUBLIC .)
