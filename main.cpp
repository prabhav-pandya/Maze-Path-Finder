#include "Utility.h"
//#include "Dijkstra.h"
//#include "AStar.h"
#include "BFS.h"

void getEndPoints(int &startCol, int &startRow, int &destCol, int &destRow, char env[ROW][COL]){
    // get positions of starting and destination points

    for(int i=0;i <ROW;i++){
        if(env[i][COL-1] == 'E') destCol = COL - 1, destRow = i;
        else if(env[i][COL-1] == 'S') startCol = COL - 1, startRow = i;
        else if(find(env[i],&env[i][COL-1],'E') - env[i] != COL-1) destCol = find(env[i], &env[i][COL - 1], 'E') - env[i], destRow = i;
        else if(find(env[i],&env[i][COL-1],'S') - env[i] != COL-1) startCol = find(env[i], &env[i][COL - 1], 'S') - env[i], startRow = i;
    }
}

void printEnv(char env[ROW][COL]){
    // print environment

    cout<<endl;
    for(int i=0;i<ROW;i++){
        for(int j=0;j<COL;j++){
            cout<<env[i][j] << ' ';
        }
        cout<<endl;
    }
}


int main() {
    int startCol,startRow,destCol,destRow;

    //create environment
    char env[ROW][COL]= {
            {'_','_','W','_','W','_','_','_','_','_'},
            {'_','_','W','_','W','_','E','_','W','_'},
            {'_','_','W','_','W','_','_','_','W','_'},
            {'_','_','W','_','W','_','_','_','W','_'},
            {'_','_','W','_','_','_','_','_','W','_'},
            {'W','W','W','W','W','W','W','W','W','_'},
            {'_','_','_','_','_','_','_','_','_','_'},
            {'_','S','_','_','_','_','_','_','_','_'},
            {'_','_','_','_','_','_','_','_','_','_'},
            {'_','_','_','_','_','_','_','_','_','_'},
    };

    getEndPoints(startCol, startRow, destCol, destRow, env);

//    Dijkstra dj;
//
//    dj.djikstra(startRow, startCol, destRow, destCol, env);

//    AStar ass;
//
//    ass.astar(startRow, startCol, destRow, destCol, env);

    BFS b;

    b.bfs(startRow, startCol, destRow, destCol, env);

    printEnv(env);

    return 0;
}
