add_library(dataset DataFrame.cpp)
set_property(TARGET dataset PROPERTY CXX_STANDARD 20)
target_include_directories(dataset PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
