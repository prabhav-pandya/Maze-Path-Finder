#include <iostream>
#include<bits/stdc++.h>
#include "PriorityQueue.h"
#include <stdlib.h>

#define ROW 10
#define COL 10

using namespace std;

void getEndPoints(int &c_s, int &r_s, int &c_e, int &r_e, char env[ROW][COL]){
    for(int i=0;i <ROW;i++){
        if(env[i][COL-1] == 'E') c_e = COL-1, r_e = i;
        else if(env[i][COL-1] == 'S') c_s = COL-1, r_s = i;
        else if(find(env[i],&env[i][COL-1],'E') - env[i] != COL-1) c_e = (find(env[i],&env[i][COL-1],'E') - env[i]), r_e = i;
        else if(find(env[i],&env[i][COL-1],'S') - env[i] != COL-1) c_s = (find(env[i],&env[i][COL-1],'S') - env[i]), r_s = i;
    }
}

int isMarked(vector<point*> marked_list, point* p){
    for(int i=0;i<marked_list.size();i++){
        if(marked_list[i]->c == p->c && marked_list[i]->r == p->r){
            return 1;
        }
    }
    return 0;
}

void printEnv(char env[ROW][COL]){
    cout<<endl;
    for(int i=0;i<ROW;i++){
        for(int j=0;j<COL;j++){
            cout<<env[i][j];
        }
        cout<<endl;
    }
}

void backTrack(point* p, char env[ROW][COL]){
    point* c = p;
    while(c->prev_point!=NULL){
        env[c->r][c->c]='X';
        c=c->prev_point;
    }
}

void djikstra(int r_s,int c_s, int r_e, int c_e, char env[ROW][COL]){

    vector<point*> marked_list;
    char env_copy[ROW][COL];
    struct point *c = new point();
    struct point *n;

    memcpy(env_copy,env,sizeof(char)*ROW*COL);
    c->r = r_s, c->c = c_s, c->dist = 0, c->prev_point = NULL;
    PriorityQueue *q = new PriorityQueue();
    q->push(c);
    int i=0;
    while(q->size()!=0){
        cout<<i++<<endl;
        //cout<<"c->r: "<<c->r<<" c->c: "<<c->c<<endl;
        if(c->r - 1 != -1 && env[c->r - 1][c->c]!='W' && env_copy[c->r - 1][c->c]!='*'){
            n = new point();
            n->r = c->r - 1,n->c = c->c, n->prev_point = c, n->dist = c->dist + 1;
            if(n->r == r_e && n->c == c_e){
                //cout<<"\nEnd Points : r:"<<n->r<<" c:"<<n->c<<endl;
                backTrack(n,env);
                return;
            }
            if(!isMarked(marked_list,n)) {
                env_copy[n->r][n->c] = '*';
                if (!q->relaxation(n)) {
                    q->push(n);
                }
            }
        }
        if(c->c - 1 != -1 && env[c->r][c->c-1]!='W' && env_copy[c->r][c->c - 1]!='*'){
            n = new point();
            n->r = c->r,n->c = c->c - 1, n->prev_point = c, n->dist = c->dist + 1;
            if(n->r == r_e && n->c == c_e){
                //cout<<"\nEnd Points : r:"<<n->r<<" c:"<<n->c<<endl;
                backTrack(n,env);
                return;
            }
            if(!isMarked(marked_list,n)) {
                env_copy[n->r][n->c] = '*';
                if (!q->relaxation(n)) {
                    q->push(n);
                }
            }
        }
        if(c->c + 1 != COL && env[c->r][c->c+1]!='W' && env_copy[c->r][c->c + 1]!='*'){
            n = new point();
            n->r = c->r,n->c = c->c + 1, n->prev_point = c, n->dist = c->dist + 1;
            if(n->r == r_e && n->c == c_e){
                //cout<<"\nEnd Points : r:"<<n->r<<" c:"<<n->c<<endl;
                backTrack(n,env);
                return;
            }
            if(!isMarked(marked_list,n)) {
                env_copy[n->r][n->c] = '*';
                if (!q->relaxation(n)) {
                    q->push(n);
                }
            }
        }
        if(c->r + 1 != ROW && env[c->r + 1][c->c]!='W' && env_copy[c->r + 1][c->c]!='*'){
            n = new point();
            n->r = c->r + 1,n->c = c->c, n->prev_point = c, n->dist = c->dist + 1;
            if(n->r == r_e && n->c == c_e){
                cout<<"\nEnd Points : r:"<<n->r<<" c:"<<n->c<<endl;
                backTrack(n,env);
                return;
            }
            if(!isMarked(marked_list,n)) {
                env_copy[n->r][n->c] = '*';
                if (!q->relaxation(n)) {
                    q->push(n);
                }
            }
        }
        printEnv(env_copy);
        q->pop();
        marked_list.push_back(c);
        c = q->top();

    }

}


int main() {
    int c_s,r_s,c_e,r_e;
    char env[ROW][COL]= {
            {'_','_','_','_','W','_','_','_','W','_'},
            {'_','_','W','_','W','_','E','_','W','_'},
            {'_','_','W','_','W','_','_','_','W','_'},
            {'_','_','W','_','W','_','_','_','W','_'},
            {'_','_','W','_','_','_','_','_','W','_'},
            {'W','_','W','W','W','W','W','W','W','_'},
            {'_','_','_','_','_','_','_','_','_','_'},
            {'_','_','_','_','_','_','_','_','_','_'},
            {'_','_','_','_','_','_','_','_','_','_'},
            {'S','_','_','_','_','_','_','_','_','_'},
    };
    getEndPoints(c_s,r_s,c_e,r_e,env);

    djikstra(r_s,c_s,r_e,c_e,env);

    printEnv(env);



    return 0;
}
