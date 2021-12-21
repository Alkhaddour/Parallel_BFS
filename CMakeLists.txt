cmake_minimum_required(VERSION 3.21)
project(parallel_BFS_openMP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-fopenmp" )

add_executable(GraphMangerTester
        tests/GraphManagerTester.cpp
        source/graphManager.cpp
        source/utils.cpp)


add_executable(Benchmark
        tests/Benchmark.cpp
        source/graphManager.cpp
        source/utils.cpp
        source/ParallelBFS.cpp
        source/SequentialBFS.cpp
        header/ParallelComputations.h)

target_include_directories(GraphMangerTester PRIVATE header/ source/)
target_include_directories(Benchmark PRIVATE header/ source/)
