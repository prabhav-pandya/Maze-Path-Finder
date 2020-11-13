#include "Dijkstra.h"

void Dijkstra::backTrack(point *endPoint, char env[ROW][COL]) {
    // backtrack and mark all the path points by X
    point *c = endPoint->prevPoint;
    while (c->prevPoint != nullptr) {
        env[c->row][c->col] = 'X';
        c = c->prevPoint;
    }
}

void Dijkstra::djikstra(int startRow, int startCol, int destRow, int destCol, char env[ROW][COL]) {

    //envcopy is basically a copy of the env/maze to record all visited points which are represented as a *
    char envCopy[ROW][COL];
    memcpy(envCopy, env, sizeof(char) * ROW * COL);

    //currPoint and nextPoint are cursors we use when iterating through the graph
    Point *currPoint = new point();
    currPoint->row = startRow, currPoint->col = startCol, currPoint->dist = 0, currPoint->prevPoint = nullptr; // initialise the cursor to starting point

    Point *nextPoint;

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

        // check if point directly ABOVE currPoint is
        // 1. within maze boundaries    AND
        // 2. not a Wall                AND
        // 3. unvisited
        if (currPoint->row - 1 != -1 && env[currPoint->row - 1][currPoint->col] != 'W' && envCopy[currPoint->row - 1][currPoint->col] != '*') {
            nextPoint = new point();
            nextPoint->prevPoint = currPoint;
            nextPoint->row = currPoint->row - 1;
            nextPoint->col = currPoint->col;
            nextPoint->dist = currPoint->dist + 1;

            // check if nextPoint is the Destination
            if (nextPoint->row == destRow && nextPoint->col == destCol) {
                backTrack(nextPoint, env);
                return;
            }

            // if not destination, mark it as visited and push it to the queue IF its distance from Start is lesser
            envCopy[nextPoint->row][nextPoint->col] = '*';
            if (!priorityQueue->relaxation(nextPoint)) {
                priorityQueue->push(nextPoint);
            }
        }

        // check if point to the LEFT of currPoint is
        // 1. within maze boundaries    AND
        // 2. not a Wall                AND
        // 3. unvisited
        if (currPoint->col - 1 != -1 && env[currPoint->row][currPoint->col - 1] != 'W' && envCopy[currPoint->row][currPoint->col - 1] != '*') {
            nextPoint = new point();
            nextPoint->prevPoint = currPoint;
            nextPoint->row = currPoint->row;
            nextPoint->col = currPoint->col - 1;
            nextPoint->dist = currPoint->dist + 1;

            // check if nextPoint is the Destination
            if (nextPoint->row == destRow && nextPoint->col == destCol) {
                backTrack(nextPoint, env);
                return;
            }

            // if not destination, mark it as visited and push it to the queue IF its distance from Start is lesser
            envCopy[nextPoint->row][nextPoint->col] = '*';
            if (!priorityQueue->relaxation(nextPoint)) {
                priorityQueue->push(nextPoint);
            }
        }

        // check if point to the RIGHT of currPoint is
        // 1. within maze boundaries    AND
        // 2. not a Wall                AND
        // 3. unvisited
        if (currPoint->col + 1 != COL && env[currPoint->row][currPoint->col + 1] != 'W' && envCopy[currPoint->row][currPoint->col + 1] != '*') {
            nextPoint = new point();
            nextPoint->prevPoint = currPoint;
            nextPoint->row = currPoint->row;
            nextPoint->col = currPoint->col + 1;
            nextPoint->dist = currPoint->dist + 1;

            // check if nextPoint is the Destination
            if (nextPoint->row == destRow && nextPoint->col == destCol) {
                backTrack(nextPoint, env);
                return;
            }

            // if not destination, mark it as visited and push it to the queue IF its distance from Start is lesser
            envCopy[nextPoint->row][nextPoint->col] = '*';
            if (!priorityQueue->relaxation(nextPoint)) {
                priorityQueue->push(nextPoint);
            }
        }

        // check if point directly BELOW currPoint is
        // 1. within maze boundaries    AND
        // 2. not a Wall                AND
        // 3. unvisited
        if (currPoint->row + 1 != ROW && env[currPoint->row + 1][currPoint->col] != 'W' && envCopy[currPoint->row + 1][currPoint->col] != '*') {
            nextPoint = new point();
            nextPoint->prevPoint = currPoint;
            nextPoint->row = currPoint->row + 1;
            nextPoint->col = currPoint->col;
            nextPoint->dist = currPoint->dist + 1;

            // check if nextPoint is the Destination
            if (nextPoint->row == destRow && nextPoint->col == destCol) {
                backTrack(nextPoint, env);
                return;
            }

            // if not destination, mark it as visited and push it to the queue IF its distance from Start is lesser
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

