//
// Created by op on 12/12/20.
//

#ifndef PATHFINDER_ALGOS_MAZEGENERATOR_H
#define PATHFINDER_ALGOS_MAZEGENERATOR_H

#include "../Utility.h"


class MazeGenerator {
private:
    int finalX, finalY;

public:
    static void resetGrid(char grid[ROW][COL]);
    static int isInBounds(int x, int y );
    void visit(char grid[ROW][COL], int x, int y);
    static void printGrid(char grid[ROW][COL]);
    void getGrid(char grid[ROW][COL]);
};


#endif //PATHFINDER_ALGOS_MAZEGENERATOR_H
