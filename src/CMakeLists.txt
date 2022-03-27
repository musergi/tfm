add_subdirectory(papi)
add_executable(test main.cpp ArgummentParser.cpp)
target_link_libraries(test PRIVATE papi_wrapper)
