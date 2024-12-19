cmake_minimum_required(VERSION 3.30)
project(librouter)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS true)

include_directories(3rdparty/uuid_v4)

add_library(librouter src/Router.cpp src/Router.h
        src/NetworkManager.cpp
        src/NetworkManager.h
        src/AdjacencyList.cpp
        src/AdjacencyList.h
        src/Hashmap.cpp
        src/Hashmap.h
        src/List.cpp
        src/List.h
)
add_executable(example example.cpp)
target_include_directories(example PRIVATE src/)
target_link_libraries(example librouter)
