cmake_minimum_required(VERSION 3.16)

project(add CXX)

include(../common.cmake)

add_subdirectory(master)
add_subdirectory(executor)
add_subdirectory(executor/benchmark)


