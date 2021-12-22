#include "AStar.h"
#include <math.h>

bool AStar::isValid(int row, int col, char envCopy[ROW][COL])
{
    // return true if row number and column number
    // is in range
    return (row >= 0) && (row < ROW) &&
           (col >= 0) && (col < COL) &&
           envCopy[row][col] != 'W' &&
           envCopy[row][col] != '*';
}

void AStar::backTrack(point *endPoint, char env[ROW][COL]) {
    // backtrack and mark all the path points by X
    point *c = endPoint->prevPoint;
    while (c->prevPoint != nullptr) {
        env[c->row][c->col] = 'X';
        c = c->prevPoint;
    }
}

void AStar::astar(int startRow, int startCol, int destRow, int destCol, char env[ROW][COL]) {

    //envcopy is basically a copy of the env/maze to record all visited points which are represented as a *
    char envCopy[ROW][COL];
    memcpy(envCopy, env, sizeof(char) * ROW * COL);

    //currPoint and nextPoint are cursors we use when iterating through the graph
    point *currPoint = new point();
    currPoint->row = startRow, currPoint->col = startCol, currPoint->cost += sqrt(pow(currPoint->row - destRow,2)+pow(currPoint->col - destCol,2)), currPoint->prevPoint = nullptr; // initialise the cursor to starting point

    point *nextPoint;

    //this priority queue holds the next unvisited points
    PriorityQueue *priorityQueue = new PriorityQueue();
    priorityQueue->push(currPoint); //push starting point in the queue

    // Check all the neighboring points to the current point
    // - ignore if the point is a wall(W)
    // - ignore if the point is already visited
    // - ignore if index is out of range
    // - update point if distance from starting point is shorter (relaxation)
    // - backtrack and return if destination point is found

    while (priorityQueue->size() != 0) {
        // These arrays are used to get row and column
        // numbers of 4 neighbours of a given cell
        int rowNum[] = {-1, 0, 0, 1};
        int colNum[] = {0, -1, 1, 0};

        // check if point directly ABOVE currPoint is
        // 1. within maze boundaries    AND
        // 2. not a Wall                AND
        // 3. unvisited

        // pop the top element and move to the next element in the queue
        currPoint = priorityQueue->top();
        priorityQueue->pop();

        for(int i=0;i<4;i++) {
            int row = currPoint->row + rowNum[i];
            int col = currPoint->col + colNum[i];
            if (isValid(row,col,envCopy)) {
                nextPoint = new point();
                nextPoint->prevPoint = currPoint;
                nextPoint->row = row;
                nextPoint->col = col;
                nextPoint->cost = sqrt(pow(row - destRow, 2) + pow(col - destCol, 2));

                // check if nextPoint is the Destination
                if (row == destRow && col == destCol) {
                    backTrack(nextPoint, env);
                    return;
                }

                // if not destination, mark it as visited and push it to the queue IF its distance from Start is lesser
                envCopy[row][col] = '*';
                if (!priorityQueue->relaxation(nextPoint)) {
                    priorityQueue->push(nextPoint);
                }
            }
        }

    }

}


