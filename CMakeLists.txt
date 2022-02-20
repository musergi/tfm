cmake_minimum_required(VERSION 3.15)
project(tfm)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/cmake")
find_package(PAPI REQUIRED)

add_executable(test main.c EventSet.c EventList.c)
target_link_libraries(test PRIVATE ${PAPI_LIBRARIES})
