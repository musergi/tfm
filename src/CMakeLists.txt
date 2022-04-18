add_subdirectory(papi)

add_executable(list list.cpp)
set_property(TARGET list PROPERTY CXX_STANDARD 20)
target_link_libraries(list PRIVATE papi_wrapper)

add_executable(record record.cpp)
set_property(TARGET record PROPERTY CXX_STANDARD 20)
target_link_libraries(record PRIVATE papi_wrapper)
