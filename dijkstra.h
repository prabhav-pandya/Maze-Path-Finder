#ifndef PATHFINDER_ALGOS_DIJKSTRA_H
#define PATHFINDER_ALGOS_DIJKSTRA_H

#include "dijkstra.h"
#include "utility.h"

class Dijkstra {
private:
    void backTrack(point* end_point, char env[ROW][COL]);
public:
    void djikstra(int start_row, int start_col, int dest_row, int dest_col, char env[ROW][COL]);
};


#endif //PATHFINDER_ALGOS_DIJKSTRA_H
