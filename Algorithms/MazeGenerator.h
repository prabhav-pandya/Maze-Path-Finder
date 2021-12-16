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
    static void resetGrid(vector<vector<char>> &grid);
    static int isInBounds(int x, int y );
    void visit(vector<vector<char>> &grid, int x, int y);
    static void printGrid(vector<vector<char>> &grid);
    void getGrid(vector<vector<char>> &grid);
    void addRandomPaths(vector<vector<char>> &grid);
};


#endif //PATHFINDER_ALGOS_MAZEGENERATOR_H
