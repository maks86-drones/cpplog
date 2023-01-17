project(wfb123)
cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES src/log.cpp)

add_library(log STATIC ${SOURCE_FILES})
set_target_properties(log PROPERTIES PUBLIC_HEADER "include/log/log.h")
target_include_directories(log PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

INSTALL(TARGETS log 
        LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_PREFIX}/include/log
)
