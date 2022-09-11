project(wfb123)
cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES src/log.cpp)

add_library(log STATIC ${SOURCE_FILES})
target_include_directories(log PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
