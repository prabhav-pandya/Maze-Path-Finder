cmake_minimum_required(VERSION 3.21)
project(Pathfinder_Algos)

set(CMAKE_CXX_STANDARD 14)

find_package(SFML 2.5 COMPONENTS graphics)
add_executable(Pathfinder_Algos main.cpp Algorithms/PriorityQueue.cpp Algorithms/PriorityQueue.h Utility.h Algorithms/MazeGenerator.cpp Algorithms/MazeGenerator.h)
target_link_libraries(Pathfinder_Algos sfml-graphics)