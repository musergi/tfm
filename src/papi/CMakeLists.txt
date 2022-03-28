add_library(papi_wrapper Event.cpp PapiException.cpp)
target_include_directories(papi_wrapper PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(papi_wrapper PUBLIC ${PAPI_LIBRARIES})
