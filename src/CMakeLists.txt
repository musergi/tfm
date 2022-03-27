add_subdirectory(papi)
add_executable(test main.cpp ArgumentParser.cpp)
target_link_libraries(test PRIVATE papi_wrapper)
