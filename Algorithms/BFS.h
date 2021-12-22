#ifndef PATHFINDER_ALGOS_BFS_H
#define PATHFINDER_ALGOS_BFS_H

#include "BFS.h"
#include "../Utility.h"
#include <queue>


class BFS {
public:
    static void backTrack(point *endPoint, char env[ROW][COL]);
    static bool isValid(int row, int col, char envCopy[ROW][COL]);
    static void bfs(int startRow, int startCol, int destRow, int destCol, char env[ROW][COL]);
};


#endif //PATHFINDER_ALGOS_BFS_H
