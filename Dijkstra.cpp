#include "Dijkstra.h"

void Dijkstra::backTrack(point *endPoint, char env[ROW][COL]) {
    // backtrack and mark all the path points by X

    point *c = endPoint;
    while (c->prevPoint != nullptr) {
        env[c->row][c->col] = 'X';
        c = c->prevPoint;
    }
}

void Dijkstra::djikstra(int startRow, int startCol, int destRow, int destCol, char env[ROW][COL]) {

    char envCopy[ROW][COL];
    memcpy(envCopy, env, sizeof(char) * ROW * COL); // create a copy of env

    Point *currPoint = new point(); // create a cursor
    currPoint->row = startRow, currPoint->col = startCol, currPoint->dist = 0, currPoint->prevPoint = nullptr; // initialise the cursor to starting point

    Point *nextPoint;

    PriorityQueue *priorityQueue = new PriorityQueue();

    priorityQueue->push(currPoint); //push starting point in the queue

    while (priorityQueue->size() != 0) {

        /*
         Check all the neighboring points to the current point
         - ignore if the point is a wall(W)
         - ignore if the point is already visited
         - ignore if index is out of range
         - update point if distance from starting point is shorter (relaxation)
         - backtrack and return if destination point is found
        */

        if (currPoint->row - 1 != -1 && env[currPoint->row - 1][currPoint->col] != 'W' && envCopy[currPoint->row - 1][currPoint->col] != '*') {
            nextPoint = new point();
            nextPoint->prevPoint = currPoint;
            nextPoint->row = currPoint->row - 1;
            nextPoint->col = currPoint->col;
            nextPoint->dist = currPoint->dist + 1;

            if (nextPoint->row == destRow && nextPoint->col == destCol) {
                backTrack(nextPoint, env);
                return;
            }
            envCopy[nextPoint->row][nextPoint->col] = '*';
            if (!priorityQueue->relaxation(nextPoint)) {
                priorityQueue->push(nextPoint);
            }
        }
        if (currPoint->col - 1 != -1 && env[currPoint->row][currPoint->col - 1] != 'W' && envCopy[currPoint->row][currPoint->col - 1] != '*') {
            nextPoint = new point();
            nextPoint->prevPoint = currPoint;
            nextPoint->row = currPoint->row;
            nextPoint->col = currPoint->col - 1;
            nextPoint->dist = currPoint->dist + 1;

            if (nextPoint->row == destRow && nextPoint->col == destCol) {
                backTrack(nextPoint, env);
                return;
            }

            envCopy[nextPoint->row][nextPoint->col] = '*';
            if (!priorityQueue->relaxation(nextPoint)) {
                priorityQueue->push(nextPoint);
            }
        }
        if (currPoint->col + 1 != COL && env[currPoint->row][currPoint->col + 1] != 'W' && envCopy[currPoint->row][currPoint->col + 1] != '*') {
            nextPoint = new point();
            nextPoint->prevPoint = currPoint;
            nextPoint->row = currPoint->row;
            nextPoint->col = currPoint->col + 1;
            nextPoint->dist = currPoint->dist + 1;

            if (nextPoint->row == destRow && nextPoint->col == destCol) {
                backTrack(nextPoint, env);
                return;
            }

            envCopy[nextPoint->row][nextPoint->col] = '*';
            if (!priorityQueue->relaxation(nextPoint)) {
                priorityQueue->push(nextPoint);
            }
        }
        if (currPoint->row + 1 != ROW && env[currPoint->row + 1][currPoint->col] != 'W' && envCopy[currPoint->row + 1][currPoint->col] != '*') {
            nextPoint = new point();
            nextPoint->prevPoint = currPoint;
            nextPoint->row = currPoint->row + 1;
            nextPoint->col = currPoint->col;
            nextPoint->dist = currPoint->dist + 1;

            if (nextPoint->row == destRow && nextPoint->col == destCol) {
                backTrack(nextPoint, env);
                return;
            }

            envCopy[nextPoint->row][nextPoint->col] = '*';
            if (!priorityQueue->relaxation(nextPoint)) {
                priorityQueue->push(nextPoint);
            }
        }

        // pop the top element and move to the next element in the queue
        priorityQueue->pop();
        currPoint = priorityQueue->top();
    }

}

