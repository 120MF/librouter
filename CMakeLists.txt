cmake_minimum_required(VERSION 3.26)

project(librouter)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(GENERATE_EXAMPLE_PROGRAM "Compile the example.cpp into an executable." ON)
option(GENERATE_BENCHMARK_TEST "Compile the benchmark source into an executable." ON)
option(GENERATE_CORRECTNESS_TEST "Compile the correctness test source into an executable." ON)

find_package(Boost CONFIG)
if (Boost_FOUND)
    message(STATUS "Boost found: ${Boost_VERSION}")
else ()
    message(STATUS "Boost not found, tests which require Boost won't be built.")
    set(${GENERATE_BENCHMARK_TEST} OFF)
    set(${GENERATE_CORRECTNESS_TEST} OFF)
endif ()

# a quick fix, create a fork of stduuid to exterminate it.
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/stduuid/cmake)
##
set(UUID_SYSTEM_GENERATOR ON)
set(UUID_USING_CXX20_SPAN ON)
set(UUID_ENABLE_INSTALL OFF)

add_subdirectory(3rdparty/stduuid)
include_directories(3rdparty/stduuid/include)

include_directories(3rdparty/bs_thread_pool/include)

include_directories(src)

add_library(librouter
        src/Router.cpp src/Router.h
        src/NetworkManager.cpp
        src/NetworkManager.h
        src/data_structure/Graph.cpp
        src/data_structure/Graph.h
        src/data_structure/Hashmap.cpp
        src/data_structure/Hashmap.h
        src/data_structure/ConcurrentHashmap.cpp
        src/data_structure/ConcurrentHashmap.h
        src/data_structure/PriorityQueue.cpp
        src/data_structure/PriorityQueue.h
        src/algorithm/DijkstraResolver.cpp
        src/algorithm/DijkstraResolver.h
        src/data_structure/Stack.cpp
        src/data_structure/Stack.h
        src/utils/HashCompute.hpp
)
target_link_libraries(librouter stduuid)

if (${GENERATE_EXAMPLE_PROGRAM})
    add_executable(example example.cpp)
    target_include_directories(example PRIVATE src/)
    target_link_libraries(example librouter)
endif ()

if (${GENERATE_CORRECTNESS_TEST})
    include(CTest)
    add_executable(TestDijkstraCorrectness tests/dijkstra_correctness_test.cpp)
    target_link_libraries(TestDijkstraCorrectness librouter)
    add_test(NAME TestDijkstraCorrectness
            COMMAND TestDijkstraCorrectness
    )
endif ()
if (${GENERATE_BENCHMARK_TEST})
    set(BENCHMARK_ENABLE_GTEST_TESTS OFF)
    add_subdirectory(3rdparty/benchmark)
    add_executable(librouter_benchmark tests/benchmark.cpp)
    target_include_directories(librouter_benchmark PRIVATE src/)
    target_link_libraries(librouter_benchmark librouter benchmark::benchmark)
endif ()