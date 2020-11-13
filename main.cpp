#include "utility.h"
#include "dijkstra.h"

void getEndPoints(int &start_col, int &start_row, int &dest_col, int &dest_row, char env[ROW][COL]){
    // get positions of starting and destination points

    for(int i=0;i <ROW;i++){
        if(env[i][COL-1] == 'E') dest_col = COL - 1, dest_row = i;
        else if(env[i][COL-1] == 'S') start_col = COL - 1, start_row = i;
        else if(find(env[i],&env[i][COL-1],'E') - env[i] != COL-1) dest_col = (find(env[i], &env[i][COL - 1], 'E') - env[i]), dest_row = i;
        else if(find(env[i],&env[i][COL-1],'S') - env[i] != COL-1) start_col = (find(env[i], &env[i][COL - 1], 'S') - env[i]), start_row = i;
    }
}

void printEnv(char env[ROW][COL]){
    // print environment

    cout<<endl;
    for(int i=0;i<ROW;i++){
        for(int j=0;j<COL;j++){
            cout<<env[i][j];
        }
        cout<<endl;
    }
}


int main() {
    int start_col,start_row,dest_col,dest_row;

    //create environment
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

    getEndPoints(start_col, start_row, dest_col, dest_row, env);

    Dijkstra dj;

    dj.djikstra(start_row, start_col, dest_row, dest_col, env);

    printEnv(env);

    return 0;
}
