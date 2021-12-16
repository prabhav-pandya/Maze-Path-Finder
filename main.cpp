#include <bits/stdc++.h>
#include <cstring>
#include <cstdlib>
#include <queue>
#include "Utility.h"
#include "Algorithms/MazeGenerator.h"
#include "Algorithms/Dijkstra.h"
#include "Algorithms/AStar.h"
#include "Algorithms/BFS.h"
#include <SFML/Graphics.hpp>


using namespace std;
struct Position{
    int row;
    int col;
    int heuristicVal;
    Position *lastPos;
    int cost;
};

int row, col;

vector<vector<char>> env;

vector<vector<char>> envClone;

int numIterations = 0;

//char playerChar = 'P';
//char wallChar = 'B';
//char goalChar = 'G';


// Compare Heuristic
class CompareHeuristic {
public:
    bool operator()(Position const& p1, Position const& p2)
    {
        return p1.heuristicVal > p2.heuristicVal;
    }
};

Position findPos(vector<vector<char>> board, char m){
    for(int i=0;i<board.size();i++){
        for(int j=0;j<board[i].size();j++){
            if(board[i][j]==m){
                return Position{i,j,0};
            }
        }
    }
}

int calculateManhattan(Position m1, Position m2){
    return abs(m1.row-m2.row) + abs(m1.col-m2.col);
}

void printSolvedEnv(Position lastPos, Position startPos){
    int len = 0;
    env[lastPos.row][lastPos.col] = goalChar;
    lastPos = *lastPos.lastPos;
    while(lastPos.row!=startPos.row || lastPos.col!=startPos.col){
        env[lastPos.row][lastPos.col] ='o';
        lastPos = *lastPos.lastPos;
        len++;
    }
    env[startPos.row][startPos.col] = playerChar;

    for(int i=0;i<env.size();i++){
        for(int j=0;j<env[i].size();j++){
            cout<<env[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<"\nPath Length: "<<len<<endl;
    cout<<"Number of iterations: "<<numIterations<<endl;
}

// can we update the window as the algorithm explores using multi threading?
int drawEnv(vector<vector<char>> env, int row, int col) {
   int squareSize = 30;
    sf::RenderWindow window(sf::VideoMode(col*squareSize, row*squareSize), "Pathfinder");
    vector<sf::RectangleShape> vec;

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            int x = i * squareSize;
            int y = j * squareSize;

            sf::RectangleShape whitecolor(sf::Vector2f(squareSize, squareSize)); //White rectangles for the board

            if (env[i][j] == wallChar) whitecolor.setFillColor(sf::Color(36, 8, 150));

            else if (env[i][j] == playerChar|| env[i][j] == goalChar) whitecolor.setFillColor(sf::Color(117, 40, 166));

            else if (env[i][j] == 'o') whitecolor.setFillColor(sf::Color(176, 66, 255));

            else if (env[i][j] == '_')  whitecolor.setFillColor(sf::Color(180, 161, 255));

            whitecolor.setPosition(sf::Vector2f(y, x));

            vec.push_back(whitecolor);
        }
    }
  while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }

        window.clear();
        for (auto &rect : vec) {
            window.draw(rect);
        }
        window.display();
    }

    return EXIT_SUCCESS;
}


void dfs(vector<vector<char>> board){
    int numRows = board.size(), numCols = board[0].size();

    Position playerPos = findPos(board, playerChar);
    Position goalPos = findPos(board, goalChar);

    playerPos.lastPos= nullptr;
    playerPos.heuristicVal = 0;

    Position currentPos;

    stack<Position> openList;
    openList.push(playerPos);

    vector<Position> closedList;

    int adjMovesRow[] = {0,1,0,-1};
    int adjMovesCol[] = {1,0,-1,0};

    while(!openList.empty()){
            currentPos = openList.top();
            if(calculateManhattan(currentPos, goalPos)==0) break;
            openList.pop();
            numIterations++;
            for(int i=0;i<4;i++){
                Position newMove = Position{currentPos.row+adjMovesRow[i], currentPos.col+adjMovesCol[i]};
                newMove.lastPos = new Position{currentPos.row, currentPos.col, currentPos.heuristicVal, currentPos.lastPos};
                if((newMove.row>=0 && newMove.col>=0 && newMove.row<numRows && newMove.col<numCols) && (board[newMove.row][newMove.col]!=wallChar)){
                    bool isInClosedList = false;
                    for(Position pos: closedList){
                        if(pos.row==newMove.row && pos.col==newMove.col){
                            isInClosedList = true;
                            break;
                        }
                    }
                    if(!isInClosedList){
                        openList.push(newMove);
                    }
                }
            }

            closedList.push_back(currentPos);
    }
    if(calculateManhattan(currentPos,goalPos)==0) printSolvedEnv(currentPos, playerPos);
    else cout<<"\nNo path exists.";
}


void dijkstra(vector<vector<char>> board) {
    int numRows = board.size(), numCols = board[0].size();

    Position playerPos = findPos(board, playerChar);
    Position goalPos = findPos(board, goalChar);

    playerPos.heuristicVal = 0;

    // maintain a open and closed list
    vector<Position> closedList;
    priority_queue<Position, vector<Position>, CompareHeuristic> openList;
    openList.push(playerPos);

    Position currentPos{};

    int adjMovesRow[] = {0,1,0,-1};
    int adjMovesCol[] = {1,0,-1,0};

    while(calculateManhattan(currentPos, goalPos)!=0 && !openList.empty()){

        currentPos = openList.top();

        envClone[currentPos.row][currentPos.col] = 'o';

        numIterations++;

        openList.pop();
        for(int i=0;i<4;i++){
            if((currentPos.row + adjMovesRow[i]<numRows && currentPos.row + adjMovesRow[i]>=0) && (currentPos.col + adjMovesCol[i]<numCols && currentPos.col + adjMovesCol[i]>=0)){
                if(board[currentPos.row+adjMovesRow[i]][currentPos.col+adjMovesCol[i]]!=wallChar){
                    Position newMove = Position{currentPos.row+adjMovesRow[i], currentPos.col+adjMovesCol[i]};

                    // check if position already exists in closed List
                    bool isInClosedList = false;
                    for(int k=0;k<closedList.size();k++){
                        if(closedList[k].row==currentPos.row && closedList[k].col==currentPos.col) isInClosedList = true;
                    }
                    newMove.heuristicVal = currentPos.heuristicVal+1;
                    Position lastPos;
                    lastPos.row = currentPos.row;
                    lastPos.col = currentPos.col;
                    lastPos.lastPos = currentPos.lastPos;
                    newMove.lastPos = new Position{currentPos.row, currentPos.col, currentPos.heuristicVal, currentPos.lastPos};
                    if(!isInClosedList) {
                        openList.push(newMove);
                    }
                }
            }
        }
        closedList.push_back(currentPos);
    }

    if(calculateManhattan(currentPos,goalPos)==0) printSolvedEnv(currentPos, playerPos);
    else cout<<"\nNo path exists.";
}




void bfs(vector<vector<char>> board){

    int numRows = board.size(), numCols = board[0].size();

    Position playerPos = findPos(board, playerChar);
    Position goalPos = findPos(board, goalChar);

    playerPos.heuristicVal = calculateManhattan(playerPos, goalPos);

    // maintain a open and closed list
    vector<Position> closedList;
    priority_queue<Position, vector<Position>, CompareHeuristic> openList;
    openList.push(playerPos);

    Position currentPos{};

    int adjMovesRow[] = {0,1,0,-1};
    int adjMovesCol[] = {1,0,-1,0};

    while(calculateManhattan(currentPos, goalPos)!=0 && !openList.empty()){

        currentPos = openList.top();

        envClone[currentPos.row][currentPos.col] = 'o';

        numIterations++;

        openList.pop();
        for(int i=0;i<4;i++){
            if((currentPos.row + adjMovesRow[i]<numRows && currentPos.row + adjMovesRow[i]>=0) && (currentPos.col + adjMovesCol[i]<numCols && currentPos.col + adjMovesCol[i]>=0)){
                if(board[currentPos.row+adjMovesRow[i]][currentPos.col+adjMovesCol[i]]!=wallChar){
                    Position newMove = Position{currentPos.row+adjMovesRow[i], currentPos.col+adjMovesCol[i]};

                    // check if position already exists in closed List
                    bool isInClosedList = false;
                    for(int k=0;k<closedList.size();k++){
                        if(closedList[k].row==currentPos.row && closedList[k].col==currentPos.col) isInClosedList = true;
                    }
                    newMove.heuristicVal = calculateManhattan(newMove, goalPos);
                    Position lastPos;
                    lastPos.row = currentPos.row;
                    lastPos.col = currentPos.col;
                    lastPos.lastPos = currentPos.lastPos;
                    newMove.lastPos = new Position{currentPos.row, currentPos.col, currentPos.heuristicVal, currentPos.lastPos};
                    if(!isInClosedList) {
                        openList.push(newMove);
                    }
                }
            }
        }
        closedList.push_back(currentPos);
    }

    if(calculateManhattan(currentPos,goalPos)==0) printSolvedEnv(currentPos, playerPos);
    else cout<<"\nNo path exists.";
}


void astar(vector<vector<char>> board){

    int numRows = board.size(), numCols = board[0].size();

    Position playerPos = findPos(board, playerChar);
    playerPos.cost = 0;
    Position goalPos = findPos(board, goalChar);

    playerPos.heuristicVal = calculateManhattan(playerPos, goalPos);

    // maintain a open and closed list
    vector<Position> closedList;
    priority_queue<Position, vector<Position>, CompareHeuristic> openList;
    openList.push(playerPos);

    Position currentPos{};

    int adjMovesRow[] = {0,1,0,-1};
    int adjMovesCol[] = {1,0,-1,0};

    while(calculateManhattan(currentPos, goalPos)!=0 && !openList.empty()){

        currentPos = openList.top();

        numIterations++;
        openList.pop();
        for(int i=0;i<4;i++){
            if((currentPos.row + adjMovesRow[i]<numRows && currentPos.row + adjMovesRow[i]>=0) && (currentPos.col + adjMovesCol[i]<numCols && currentPos.col + adjMovesCol[i]>=0)){
                if(board[currentPos.row+adjMovesRow[i]][currentPos.col+adjMovesCol[i]]!=wallChar){
                    Position newMove = Position{currentPos.row+adjMovesRow[i], currentPos.col+adjMovesCol[i]};

                    // check if position already exists in closed List
                    bool isInClosedList = false;
                    for(int k=0;k<closedList.size();k++){
                        if(closedList[k].row==currentPos.row && closedList[k].col==currentPos.col) isInClosedList = true;
                    }
                    newMove.cost = currentPos.cost+1;
                    newMove.heuristicVal = calculateManhattan(newMove, goalPos) + newMove.cost;
                    Position lastPos;
                    lastPos.row = currentPos.row;
                    lastPos.col = currentPos.col;
                    lastPos.lastPos = currentPos.lastPos;
                    newMove.lastPos = new Position{currentPos.row, currentPos.col, currentPos.heuristicVal, currentPos.lastPos};
                    if(!isInClosedList) {
                        openList.push(newMove);
                    }
                }
            }
        }
        closedList.push_back(currentPos);
    }
    if(calculateManhattan(currentPos,goalPos)==0) printSolvedEnv(currentPos, playerPos);
    else cout<<"\nNo path exists.";

}



/*
 Maze Input Example
    __________
    __________
    ___P__B___
    __BBBBB___
    ___G______

    ______G_
    _B____B_
    _B_B__B_
    _B____B_
    _BBBBBB_
    P_______

*/

void printEnv(){
    for(int i=0;i<env.size();i++){
        for(int j=0;j<env[i].size();j++){
            cout<<env[i][j]<<" ";
        }
        cout<<endl;
    }
}




int main()
{
    char ch;
    cout<<"Would you like to automatically generate a maze or design one manually? (y/n) "<<endl;
    cin>>ch;

    if(ch=='y'){
        cout<<"\nDesign your matrix:\n>Use _ for empty tiles\n>Use B for wall blocks\n>Use P & G to position your playerChar & goal respectively\n"<<endl;
        bool end = false;
        cout<<"\nEnter Number of rows and cols: ";
        cin>>row>>col;

        for(int i=0;i<row;i++){
        vector<char> row;
        for(int j=0;j<col;j++){
            char el;
            cin>>el;
            row.push_back(el);
        }
        env.push_back(row);
    }
    }
    else{
        env = vector<vector<char>>(ROW, vector<char>(COL, ' '));
        MazeGenerator mazeGenerator{};
        mazeGenerator.getGrid(env);
        row = ROW;
        col = COL;
    }

    envClone = env;

    int choice;
    cout<<"\nChoose:\n1. Best First Search\n2. A*\n3. Dijkstra\n4. DFS\n";
    cin>>choice;
    switch(choice){
        case 1: bfs(env);
            break;
        case 2: astar(env);
            break;
        case 3: dijkstra(env);
            break;
        case 4: dfs(env);
            break;
        default: cout<<"\nWrong input!";
            break;
    }
    drawEnv(env, row, col);

    return 0;
}
