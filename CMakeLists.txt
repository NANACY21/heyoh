# cmake_minimum_required(VERSION <specify CMake version here>)
project(heyoh)

set(CMAKE_CXX_STANDARD 14)

#add_executable(heyoh main.cpp)
#add_executable(heyoh algorithm/Graph/Dijkstra.cpp)
add_executable(heyoh algorithm/stackqueue.cpp)
add_executable(stackqueue algorithm/stackqueue.cpp)