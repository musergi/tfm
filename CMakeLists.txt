cmake_minimum_required(VERSION 3.15)
project(tfm)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/cmake")
find_package(PAPI REQUIRED)

add_subdirectory(src)
