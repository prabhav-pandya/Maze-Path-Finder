#ifndef PATHFINDER_ALGOS_BFS_H
#define PATHFINDER_ALGOS_BFS_H

#include "BFS.h"
#include "Utility.h"
#include <queue>

typedef struct node{
    int row;
    int col;
    point *prevPoint;
    int cost;
} node;

class BFS {
private:
    void backTrack(point *endPoint, char env[ROW][COL]);
    bool isValid(int row, int col, char envCopy[ROW][COL]);
public:
    void bfs(int startRow, int startCol, int destRow, int destCol, char env[ROW][COL]);
};


#endif //PATHFINDER_ALGOS_BFS_H
