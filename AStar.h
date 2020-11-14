#ifndef PATHFINDER_ALGOS_ASTAR_H
#define PATHFINDER_ALGOS_ASTAR_H


#include "AStar.h"
#include "Utility.h"

class AStar {
private:
    static void backTrack(point *endPoint, char env[ROW][COL]);
    static bool isValid(int row, int col, char env[ROW][COL]);

public:
    static void astar(int startRow, int startCol, int destRow, int destCol, char env[ROW][COL]);
};



#endif //PATHFINDER_ALGOS_ASTAR_H
