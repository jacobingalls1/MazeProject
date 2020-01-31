#ifndef MAZE_H
#define MAZE_H
#include <vector>
#include "point.h"

using namespace std;


class Maze{
private:
    vector<int> ori;
    int xSize, ySize;
    vector<int> player;
    vector<vector<int>> moves = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};//{>, v, <, ^};
    vector<vector<bool>> maze;
    vector<Point> enemies;
public:
    vector<int> end;
    bool dead;
    bool win;
    Maze(int xSize, int ySize, Point origin=Point(1, 1));
    int getX();
    int getY();
    vector<int> getPlayer();
    vector<vector<bool>> getMaze();
    vector<vector<bool>> emptyMaze(int xSize, int ySize);
    void populateMaze(Point origin);
    bool mazeAt(Point target);
    bool inMaze(Point target);
    bool validSpace(Point target);
    vector<Point> getMoves(Point target);
    void setTile(Point target, bool newValue);
    Point step(Point target);
    vector<Point> getPathRand(Point posI);
    void mazePrint();

    bool enemyAt(Point target);
    void enemyMove();
    void update();
    void left();
    void right();
    void up();
    void down();
};

#endif
