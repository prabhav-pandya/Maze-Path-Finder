#ifndef PATHFINDER_ALGOS_DIJKSTRA_H
#define PATHFINDER_ALGOS_DIJKSTRA_H


#include "Dijkstra.h"
#include "../Utility.h"

class Dijkstra {
private:
    static void backTrack(point *endPoint, char env[ROW][COL]);
    static bool isValid(int row, int col, char env[ROW][COL]);
public:
    static void djikstra(int startRow, int startCol, int destRow, int destCol, char env[ROW][COL]);
};


#endif //PATHFINDER_ALGOS_DIJKSTRA_H
