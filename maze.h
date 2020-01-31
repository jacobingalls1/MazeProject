#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include "point.h"
using namespace std;

#include <SFML/Graphics.hpp>
using namespace sf;

class Maze{
private:
    Point ori;
    int xSize, ySize;
    Point player;
    Vector2f playerV;
    vector<vector<int>> moves = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};//{>, v, <, ^};
    vector<vector<bool>> maze;
    vector<Point> enemies;
public:
    Point end;
    bool dead;
    bool win;
    Maze(int xSize, int ySize, Point origin=Point(1, 1));
    int getX();
    int getY();
    int getFace();
    Vector2i getPlayer();
    Point playerP();
    Vector2f getPlayerOff();
    Vector2f getPlayerF();
    vector<vector<bool>> getMaze();
    vector<vector<bool>> emptyMaze(int xSize, int ySize);
    void populateMaze(Point origin);
    bool mazeAt(Point target);
    bool mazeAt(Vector2i target);
    bool inMaze(Point target);
    bool validSpace(Point target);
    vector<Point> getMoves(Point target);
    void setTile(Point target, bool newValue);
    Point step(Point target);
    vector<Point> getPathRand(Point posI);
    bool los(Point target);
    float distance(Vector2i v);
    void ins(vector<Vector2i> &v, Vector2i targ);
    void insWalls(vector<Vector2i> &v, Vector2i targ);
    vector<Vector2i> los();
    void mazePrint();

    bool enemyAt(Point target);
    void enemyMove();
    void playerMove();
    void update(int toTurn);
    Vector2f rightDir();
    Vector2f downDir();
    void left();
    void right();
    void up();
    void down();
};

#endif
