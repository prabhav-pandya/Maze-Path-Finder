#include "BFS.h"

void BFS::backTrack(point *endPoint, char env[ROW][COL]) {
    // backtrack and mark all the path points by X
    point *c = endPoint->prevPoint;
    while (c->prevPoint != nullptr) {
        env[c->row][c->col] = 'X';
        c = c->prevPoint;
    }
}


bool BFS::isValid(int row, int col, char envCopy[ROW][COL])
{
    // return true if row number and column number
    // is in range
    return (row >= 0) && (row < ROW) &&
           (col >= 0) && (col < COL) &&
           envCopy[row][col] != 'W' &&
           envCopy[row][col] != '*';
}

void BFS::bfs(int startRow, int startCol, int destRow, int destCol, char env[ROW][COL]){
    //create a copy of the environment
    char envCopy[ROW][COL];
    memcpy(envCopy, env, ROW*COL*sizeof(char));

    // These arrays are used to get row and column
    // numbers of 4 neighbours of a given cell
    int rowNum[] = {-1, 0, 0, 1};
    int colNum[] = {0, -1, 1, 0};

    //currPoint and nextPoint are cursors we use when iterating through the graph
    point *nextPoint, *currPoint = new point();
    currPoint->row = startRow, currPoint->col = startCol, currPoint->cost = 0, currPoint->prevPoint = nullptr; // initialise the cursor to starting point
    envCopy[startRow][startCol] = '*';

    //initialise a Queue
    queue<point*> q;
    q.push(currPoint);

    while(!q.empty()){
        for(int i=0;i<4;i++){
            int row = currPoint->row + rowNum[i];
            int col = currPoint->col + colNum[i];
            if (isValid(row,col,envCopy)) {
                nextPoint = new point();
                nextPoint->prevPoint = currPoint;
                nextPoint->row = row;
                nextPoint->col = col;
                nextPoint->cost += 1;

                // check if nextPoint is the Destination
                if (row == destRow && col == destCol) {
                    backTrack(nextPoint, env);
                    return;
                }
                envCopy[row][col] = '*';
                q.push(nextPoint);

            }
        }
        q.pop();
        currPoint = q.front();
    }



}
