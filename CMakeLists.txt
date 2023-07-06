cmake_minimum_required(VERSION 3.15)

project(DFCPP LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
endif()
add_compile_options(-march=native)

option(DFCPP_NUMA "enable numa optimization" ON)
option(DFCPP_WORK_PUSHING "enable work pushing in numa" ON)
option(DFCPP_NUMA_ALLOC "enable numa allocation " ON)
option(DFCPP_NUMA_STEAL "enable steal local task first" ON)
option(DFCPP_WORKER_ADJUSTMENT "enable adjust the worker num in numa" ON)
option(DFCPP_STEAL_PRIORITY "enable the remote thief has less priority than local thief" ON)
option(DFCPP_DFV_COUNT "enable to auto release the DFV when it won't be needed" ON)

option(DFCPP_BUILD_BENCHMARK "enable to build benchmarks" ON)
option(DFCPP_BUILD_EXAMPLE  "enable to build examples" ON)


if(DFCPP_NUMA)
  message(STATUS "enable NUMA optimization")
  add_definitions(-DDFCPP_NUMA)
else()
  message(STATUS "disable NUMA optimization")
endif()

if(DFCPP_NUMA AND DFCPP_WORK_PUSHING)
  message(STATUS "enable work pushing in numa")
  add_definitions(-DDFCPP_WORK_PUSHING)
endif()

if(DFCPP_NUMA AND DFCPP_NUMA_ALLOC)
  message(STATUS "enable numa allocation")
  add_definitions(-DDFCPP_NUMA_ALLOC)
endif()

if(DFCPP_NUMA AND DFCPP_NUMA_STEAL)
  message(STATUS "enable steal local task first")
  add_definitions(-DDFCPP_NUMA_STEAL)
endif()

if(DFCPP_NUMA AND DFCPP_WORKER_ADJUSTMENT)
  message(STATUS "enable adjust the worker num in numa")
  add_definitions(-DDFCPP_WORKER_ADJUSTMENT)
endif()

if(DFCPP_NUMA AND DFCPP_STEAL_PRIORITY)
  message(STATUS "enable the remote thief has less priority than local thief")
  add_definitions(-DDFCPP_STEAL_PRIORITY)
endif()

if(DFCPP_DFV_COUNT)
  message(STATUS "enable to auto release the DFV when it won't be needed")
  add_definitions(-DDFCPP_DFV_COUNT)
endif()

include_directories(${PROJECT_SOURCE_DIR})
if(DFCPP_BUILD_EXAMPLES)
add_subdirectory(examples)
endif()

if(DFCPP_BUILD_BENCHMARK)
add_subdirectory(benchmark)
endif()