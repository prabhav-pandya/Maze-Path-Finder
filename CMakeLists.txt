cmake_minimum_required(VERSION 3.17)
project(Pathfinder_Algos)

set(CMAKE_CXX_STANDARD 14)

add_executable(Pathfinder_Algos main.cpp Dijkstra.cpp Dijkstra.h PriorityQueue.cpp PriorityQueue.h Utility.h AStar.cpp AStar.h BFS.cpp BFS.h)