#ifndef PATHFINDER_ALGOS_PRIORITYQUEUE_H
#define PATHFINDER_ALGOS_PRIORITYQUEUE_H


#include "PriorityQueue.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>
using namespace std;

typedef struct point{
    int row;
    int col;
    point *prevPoint;
    int dist;
} point;

struct PriorityQueue
{
private:
    vector<point*> A;
    int PARENT(int i);
    int LEFT(int i);
    int RIGHT(int i);
    void heapify_down(int i);
    void heapify_up(int i);

public:
    unsigned int size();
    bool empty();
    void push(point* key);
    void pop();
    point* top();
    int relaxation(point *p);
};



#endif //PATHFINDER_ALGOS_PRIORITYQUEUE_H
