#include <vector>
#include <iostream>
#include <cmath>
#include "maze.h"
#include "point.h"
using namespace std;

#include <SFML/Graphics.hpp>
using namespace sf;

Maze::Maze(int x, int y, Point origin) {
    xSize = x;
    ySize = y;
    player = {origin.x, origin.y};
    moves = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};//{>, v, <, ^}
    maze = emptyMaze(x, y);
    enemies = {};
    dead = false;
    win = false;
    cout << "Generating maze..." << endl;
    populateMaze(origin);
    setTile(Point(0, 1), true);
    int i = ySize - 2;
    cout << "Making exits..." << endl;
    while (true) {
        if (mazeAt(Point(xSize - 2, i))) {
            setTile(Point(xSize - 1, i), true);
            end = {xSize - 1, i};
            break;
        } else {
            i--;
        }
    }
    cout << "Placing enemies..." << endl;
    for (int i = 0; i < (x * x / 49); i++) {
        Point ij((rand() % (x - 2) + 1), (rand() % (x - 2) + 1));
        while (!mazeAt(ij)) {
            ij = Point((rand() % (x - 2) + 1), (rand() % (x - 2) + 1));
        }
        enemies.push_back(ij);
    }
    for (int i = 0; i < (xSize * xSize / 35); i++) {
        Point ij((rand() % (x - 2) + 1), (rand() % (x - 2) + 1));
        while (true) {
            if (!mazeAt(ij)) {
                break;
            }
            ij = Point((rand() % (x - 2) + 1), (rand() % (x - 2) + 1));

        }
        setTile(ij, true);
    }
    cout << "Your maze is ready!" << endl;
}

int Maze::getX() {
    return xSize;
}
int Maze::getY() {
    return ySize;
}
vector<int> Maze::getPlayer() {
    return player;
}

vector<vector<bool>> Maze::getMaze() {
    return maze;
}

vector<vector<bool>> Maze::emptyMaze(int x, int y) {
    vector<vector<bool>> output = {};
    for(int i = 0; i < y; i++) {
        vector<bool> row = {};
        for(int j = 0; j < x; j++) {
            row.push_back(false);
        }
        output.push_back(row);
    }
    return output;
}

void Maze::populateMaze(Point origin) {
    getPathRand(origin);
    for (int i = 1; i < xSize - 1; i++) {
        for (int j = 1; j < ySize - 1; j++) {
            if (mazeAt(Point(i, j))) {
                getPathRand(Point(i, j));
            }
        }
    }
}

bool Maze::mazeAt(Point target) {
    return maze[target.x][target.y];
}

bool Maze::inMaze(Point target) {
    return target.verify() and target.x < xSize - 1 and target.y < ySize - 1;
}

bool Maze::validSpace(Point target) {
    if (!inMaze(target) or mazeAt(target)) {
        return false;
    }
    int count = 0;
    vector<Point> gotMoves = getMoves(target);
    for (int i = 0; i < gotMoves.size(); i++) {
        if (mazeAt(gotMoves[i])) {
            count++;
        }
    }
    return inMaze(target) and count == 1;
}

vector<Point> Maze::getMoves(Point target) {
    vector<Point> final = {};
    for (int i = 0; i < moves.size(); i++) {
        final.push_back(target.vectAdd(moves[i]));
    }
    return final;
}

void Maze::setTile(Point target, bool value) {
    maze[target.x][target.y] = value;
}

Point Maze::step(Point target) {
    vector<Point> movesPossible = {};
    for (int i = 0; i < 4; i++) {
        if (validSpace(target.vectAdd(moves[i]))) {
            movesPossible.push_back(target.vectAdd(moves[i]));
        }
    }
    if (movesPossible.empty()) {
        return target;
    }
    return movesPossible[rand() % movesPossible.size()];
}

vector<Point> Maze::getPathRand(Point posI) {
    setTile(posI, true);
    vector<Point> path = {posI};
    while (true) {
        Point step = this->step(path[path.size() - 1]);
        if (step == path[path.size() - 1]) {
            break;
        } else {
            path.push_back(step);
            setTile(step, true);
        }
    }
    return path;
}

void Maze::mazePrint() {
    for (int i = 0; i < maze.size(); i++) {
        for(int j = 0; j < maze[i].size(); j++) {
            if(maze[i][j]) {
                cout << "  ";
            }else {
                cout << "# ";
            }
        }
        cout << endl;
    }
}

bool Maze::enemyAt(Point target) {
    for (int i = 0; i < enemies.size(); i++) {
        if (enemies[i] == target) {
            return true;
        }
    }
    return false;
}

void Maze::enemyMove() {
    for (int i = 0; i < enemies.size(); i++) {
        vector<Point> gotMoves = getMoves(enemies[i]), movesPoss = {};
        for (int j = 0; j < 4; j++) {
            if (mazeAt(gotMoves[j]) and inMaze(gotMoves[j])) {
                movesPoss.push_back(gotMoves[j]);
            }
        }
        enemies[i] = movesPoss.at(rand() % movesPoss.size());
        if (enemies[i] == Point(player[0], player[1])) {
            dead = true;
        }
    }
}

void Maze::update() {
    if (enemyAt(Point(player[0], player[1])) and !win) {
        dead = true;
    }
    if (player == end and !dead) {
        win = true;
    }
}

void Maze::left() {
    if (player[0] != 1 and mazeAt(Point(player[0] - 1, player[1]))) {
        player[0]--;
    }
    update();
}
void Maze::right() {
    if (player[0] != xSize - 1 and mazeAt(Point(player[0] + 1, player[1]))) {
        player[0]++;
    }
    update();
}
void Maze::up() {
    if (player[1] != 1 and mazeAt(Point(player[0], player[1] - 1))) {
        player[1]--;
    }
    update();
}
void Maze::down() {
    if (player[1] != ySize - 1 and mazeAt(Point(player[0], player[1] + 1))) {
        player[1]++;
    }
    update();
}

