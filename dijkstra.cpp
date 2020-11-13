#include "dijkstra.h"

void Dijkstra::backTrack(point* end_point, char env[ROW][COL]){
    // backtrack and mark all the path points by X

    point* c = end_point;
    while(c->prev_point!=NULL){
        env[c->r][c->c]='X';
        c=c->prev_point;
    }
}

void Dijkstra::djikstra(int start_row, int start_col, int dest_row, int dest_col, char env[ROW][COL]){

    char env_copy[ROW][COL];
    memcpy(env_copy,env,sizeof(char)*ROW*COL); // create a copy of env

    struct point *c = new point(); // create a cursor
    c->r = start_row, c->c = start_col, c->dist = 0, c->prev_point = NULL; // initialise the cursor to starting point

    struct point *n;

    PriorityQueue *q = new PriorityQueue();

    q->push(c); //push starting point in the queue

    while(q->size()!=0){

        /*
         Check all the neighboring points to the current point
         - ignore if the point is a wall(W)
         - ignore if the point is already visited
         - ignore if index is out of range
         - update point if distance from starting point is shorter (relaxation)
         - backtrack and return if destination point is found
        */

        if(c->r - 1 != -1 && env[c->r - 1][c->c]!='W' && env_copy[c->r - 1][c->c]!='*'){
            n = new point();
            n->r = c->r - 1,n->c = c->c, n->prev_point = c, n->dist = c->dist + 1;
            if(n->r == dest_row && n->c == dest_col){
                backTrack(n,env);
                return;
            }
            env_copy[n->r][n->c] = '*';
            if (!q->relaxation(n)) {
                q->push(n);
            }

        }
        if(c->c - 1 != -1 && env[c->r][c->c-1]!='W' && env_copy[c->r][c->c - 1]!='*'){
            n = new point();
            n->r = c->r,n->c = c->c - 1, n->prev_point = c, n->dist = c->dist + 1;
            if(n->r == dest_row && n->c == dest_col){
                backTrack(n,env);
                return;
            }

            env_copy[n->r][n->c] = '*';
            if (!q->relaxation(n)) {
                q->push(n);
            }

        }
        if(c->c + 1 != COL && env[c->r][c->c+1]!='W' && env_copy[c->r][c->c + 1]!='*'){
            n = new point();
            n->r = c->r,n->c = c->c + 1, n->prev_point = c, n->dist = c->dist + 1;
            if(n->r == dest_row && n->c == dest_col){
                backTrack(n,env);
                return;
            }

            env_copy[n->r][n->c] = '*';
            if (!q->relaxation(n)) {
                q->push(n);
            }

        }
        if(c->r + 1 != ROW && env[c->r + 1][c->c]!='W' && env_copy[c->r + 1][c->c]!='*'){
            n = new point();
            n->r = c->r + 1,n->c = c->c, n->prev_point = c, n->dist = c->dist + 1;
            if(n->r == dest_row && n->c == dest_col){
                backTrack(n,env);
                return;
            }

            env_copy[n->r][n->c] = '*';
            if (!q->relaxation(n)) {
                q->push(n);
            }

        }

        // pop the top element and move to the next element in the queue
        q->pop();
        c = q->top();
    }

}

