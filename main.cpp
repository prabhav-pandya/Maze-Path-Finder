#include "Utility.h"
#include "Algorithms/MazeGenerator.h"
#include "Algorithms/Dijkstra.h"
#include "Algorithms/AStar.h"
#include "Algorithms/BFS.h"
#include <SFML/Graphics.hpp>

void getEndPoints(int &startCol, int &startRow, int &destCol, int &destRow, char env[ROW][COL]) {
    // get positions of starting and destination points

    for (int i = 0; i < ROW; i++) {
        if (env[i][COL - 1] == 'E') destCol = COL - 1, destRow = i;
        else if (env[i][COL - 1] == 'S') startCol = COL - 1, startRow = i;
        else if (find(env[i], &env[i][COL - 1], 'E') - env[i] != COL - 1)
            destCol =
                    find(env[i], &env[i][COL - 1], 'E') -
                    env[i], destRow = i;
        else if (find(env[i], &env[i][COL - 1], 'S') - env[i] != COL - 1)
            startCol =
                    find(env[i], &env[i][COL - 1], 'S') -
                    env[i], startRow = i;
    }
}

void printEnv(char env[ROW][COL]) {
    cout << endl;
    for (int j = 0; j < COL; j++) {
        for (int i = 0; i < ROW; i++) {
            cout << env[i][j] << ' ';
        }
        cout << endl;
    }
}

int drawEnv(char env[ROW][COL]) {

    sf::RenderWindow window(sf::VideoMode(ROW * 50, COL * 50), "Pathfinder");
    vector<sf::RectangleShape> vec;

    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            if (env[i][j] == 'W') {
                int x = i * 50;
                int y = j * 50;

                sf::RectangleShape whitecolor(sf::Vector2f(50, 50)); //White rectangles for the board
                whitecolor.setFillColor(sf::Color(128, 128, 128));
                whitecolor.setPosition(sf::Vector2f(x, y));
                vec.push_back(whitecolor);
            }
            if (env[i][j] == 'S' || env[i][j] == 'E') {
                int x = i * 50;
                int y = j * 50;

                sf::RectangleShape whitecolor(sf::Vector2f(50, 50)); //White rectangles for the board
                whitecolor.setFillColor(sf::Color::Red);
                whitecolor.setPosition(sf::Vector2f(x, y));
                vec.push_back(whitecolor);
            }
            if (env[i][j] == 'X') {
                int x = i * 50;
                int y = j * 50;

                sf::RectangleShape whitecolor(sf::Vector2f(50, 50)); //White rectangles for the board
                whitecolor.setFillColor(sf::Color::Green);
                whitecolor.setPosition(sf::Vector2f(x, y));
                vec.push_back(whitecolor);
            }
            if (env[i][j] == '_') {
                int x = i * 50;
                int y = j * 50;

                sf::RectangleShape whitecolor(sf::Vector2f(50, 50)); //White rectangles for the board
                whitecolor.setFillColor(sf::Color(211, 211, 211));
                whitecolor.setPosition(sf::Vector2f(x, y));
                vec.push_back(whitecolor);
            }
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


int main() {
    int startCol, startRow, destCol, destRow;

    //create environment
    char env[ROW][COL];
    MazeGenerator mazeGenerator{};
    mazeGenerator.getGrid(env);
    getEndPoints(startCol, startRow, destCol, destRow, env);

//    Dijkstra::djikstra(startRow, startCol, destRow, destCol, env);
    AStar::astar(startRow, startCol, destRow, destCol, env);
//    BFS::bfs(startRow, startCol, destRow, destCol, env);

    printEnv(env);
    drawEnv(env);
}
