cmake_minimum_required(VERSION 3.10)
project(MatrixProject)

set(CMAKE_CXX_STANDARD 11)

find_package(GTest REQUIRED)

add_library(MatrixLib Matrix.cpp)

add_executable(matrix_tests MatrixTests.cpp)
target_link_libraries(matrix_tests MatrixLib GTest::GTest GTest::Main)

enable_testing()
add_test(NAME MatrixTests COMMAND matrix_tests)