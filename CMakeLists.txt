cmake_minimum_required(VERSION 3.17)
project(Pathfinder_Algos)

set(CMAKE_CXX_STANDARD 14)

find_package(SFML 2.5 COMPONENTS graphics)
add_executable(Pathfinder_Algos main.cpp Algorithms/Dijkstra.cpp Algorithms/Dijkstra.h Algorithms/PriorityQueue.cpp Algorithms/PriorityQueue.h Utility.h Algorithms/AStar.cpp Algorithms/AStar.h Algorithms/BFS.cpp Algorithms/BFS.h Algorithms/MazeGenerator.cpp Algorithms/MazeGenerator.h)
target_link_libraries(Pathfinder_Algos sfml-graphics)