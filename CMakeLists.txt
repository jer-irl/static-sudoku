cmake_minimum_required(VERSION 3.7)
project(static-sudoku)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_subdirectory(src)
add_subdirectory(test)