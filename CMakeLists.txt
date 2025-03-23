cmake_minimum_required(VERSION 3.29)
project(QuineMcCluskeySolver)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(external/googletest)

add_subdirectory(src)

option(BUILD_TESTS "Build tests" ON)
if(BUILD_TESTS)
    add_subdirectory(tests)
endif()
