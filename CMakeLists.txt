cmake_minimum_required(VERSION 3.30)
project(librouter)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS true)

add_library(librouter src/Router.cpp src/Router.h
        src/NetworkManager.cpp
        src/NetworkManager.h
        src/AdjacencyList.cpp
        src/AdjacencyList.h
        src/Hashmap.cpp
        src/Hashmap.h
)
add_executable(example example.cpp)
target_include_directories(example PRIVATE src/)
target_link_libraries(example librouter)
