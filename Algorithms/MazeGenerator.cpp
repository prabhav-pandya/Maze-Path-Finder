#include "MazeGenerator.h"

void MazeGenerator::getGrid(vector<vector<char>> &grid) {
    srand(time(nullptr));
    resetGrid(grid);
    visit(grid, 0, 0);
    grid[0][0] = playerChar;
    grid[finalX][finalY] = goalChar;
    addRandomPaths(grid);
    printGrid(grid);
}

void MazeGenerator::addRandomPaths(vector<vector<char>> &grid){
    for(int i=0;i<ROW;i++){
        for(int j=0;j<COL;j++){
            if(grid[i][j]==wallChar){
              int randomVal = rand() & 10;
              if(randomVal>9){
                grid[i][j]='_';
              }
            }
        }
    }
}

void MazeGenerator::resetGrid(vector<vector<char>> &grid) {
    for (int x = 0; x < ROW; ++x) {
        for (int y = 0; y < COL; ++y) {
            grid[x][y] = wallChar;
        }
    }
}

int MazeGenerator::isInBounds(int x, int y) {
    if (x < 0 || x >= ROW) return false;
    if (y < 0 || y >= COL) return false;
    return true;
}


void MazeGenerator::visit(vector<vector<char>> &grid, int x, int y) {
    this->finalX = x;
    this->finalY = y;
    grid[x][y] = '_';

    int dirs[4];
    dirs[0] = NORTH;
    dirs[1] = EAST;
    dirs[2] = SOUTH;
    dirs[3] = WEST;
    for (int &dir : dirs) {
        int r = rand() & 3;
        int temp = dirs[r];
        dirs[r] = dir;
        dir = temp;
    }

    for (int dir : dirs) {
        int dx = 0, dy = 0;
        switch (dir) {
            case NORTH:
                dy = -1;
                break;
            case SOUTH:
                dy = 1;
                break;
            case EAST:
                dx = 1;
                break;
            case WEST:
                dx = -1;
                break;
            default:
                break;
        }

        int x2 = x + (dx << 1);
        int y2 = y + (dy << 1);
        if (isInBounds(x2, y2)) {
            if (grid[x2][y2] == wallChar) {
                grid[x2 - dx][y2 - dy] = '_';
                this->visit(grid, x2, y2);
            }
        }
    }
}

void MazeGenerator::printGrid(vector<vector<char>> &grid) {
    for (int y = 0; y < COL; ++y) {
        for (int x = 0; x < ROW; ++x) {
            cout << grid[x][y] << ' ';
        }
        cout << endl;
    }
}
