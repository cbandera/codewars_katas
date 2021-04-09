cmake_minimum_required(VERSION 3.10)
project(codewars_katas)
Include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v2.13.1)
FetchContent_MakeAvailable(Catch2)
FetchContent_GetProperties(Catch2 SOURCE_DIR Catch2srcDir)
list(APPEND CMAKE_MODULE_PATH ${Catch2srcDir}/contrib)

set(BENCHMARK_ENABLE_GTEST_TESTS OFF)
set(BENCHMARK_ENABLE_TESTING OFF)
FetchContent_Declare(
  Benchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG        v1.5.2)
FetchContent_MakeAvailable(Benchmark)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic") #  -Werror
if("${CMAKE_BUILD_TYPE}" MATCHES "Debug")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-limit-debug-info")
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
endif()

file(GLOB_RECURSE lib_files src/*)
add_library(my_lib INTERFACE)
target_include_directories(my_lib INTERFACE src/)

file(GLOB_RECURSE test_files test/*)
add_executable(unittests ${test_files})
target_link_libraries(unittests PRIVATE my_lib Catch2::Catch2)


file(GLOB_RECURSE benchmark_files benchmarks/*)
foreach(benchmark_file IN LISTS benchmark_files)
  get_filename_component(exe_name ${benchmark_file} NAME_WE)
  if(NOT TARGET ${exe_name})
    add_executable(${exe_name} ${benchmark_file})
    target_link_libraries(${exe_name} PRIVATE my_lib benchmark::benchmark)
  endif()
endforeach()


include(CTest)
include(Catch)
catch_discover_tests(unittests)
