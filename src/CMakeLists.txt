add_subdirectory(papi)
add_executable(test main.cpp ArgumentParser.cpp)
set_property(TARGET test PROPERTY CXX_STANDARD 20)
target_link_libraries(test PRIVATE papi_wrapper)
