# cmake_minimum_required(VERSION <specify CMake version here>)
project(heyoh)

set(CMAKE_CXX_STANDARD 14)

#add_executable(heyoh main.cpp)
#add_executable(heyoh algorithm/Graph/Dijkstra.cpp)
#add_executable(heyoh algorithm/stackqueue.cpp)
add_executable(stackqueue algorithm/stackqueue.cpp)
add_executable(实验6 datastructure/实验6.cpp)
add_executable(vectorheap algorithm/vectorheap.cpp)
add_executable(algorithm algorithm/algorithm.cpp)