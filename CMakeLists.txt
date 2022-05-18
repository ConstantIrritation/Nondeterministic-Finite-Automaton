cmake_minimum_required(VERSION 2.8)

project(NFA)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib")

set(CMAKE_CXX_STANDARD 11)
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

include_directories("${PROJECT_SOURCE_DIR}/lib")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

set(SOURCE_FOR_TEST ${PROJECT_SOURCE_DIR}/test/main_test.cpp)

add_executable(NFA ${PROJECT_SOURCE_DIR}/src/main.cpp)
target_link_libraries(NFA Autom)

add_subdirectory(${PROJECT_SOURCE_DIR}/lib)

enable_testing()
add_executable(CTest ${SOURCE_FOR_TEST})
target_link_libraries(CTest gtest gtest_main pthread Autom)
