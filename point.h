#ifndef CHESS_POINT_H
#define CHESS_POINT_H

#include <vector>
#include <iostream>
using namespace std;

#include <SFML/Graphics.hpp>
using namespace sf;

class Point {
public:
    float x, y;
    int facing;
    int xI();
    float xF();
    int yI();
    float yF();
    float getAngle();
    Vector2f pos();
    Point(float xPos=1, float yPos=1, int facing=0);
    Point(Vector2f pos, int facing=0);
    Point(Vector2i pos, int facing=0);
    bool operator==(Point);
    void add(Point toAdd);
    Point vectAdd(vector<int> toAdd);
    Point vectAdd(Vector2f toAdd);
    bool verify();
    void turn(int amt);
    bool isIn(vector<Point>);
};


#endif //CHESS_POINT_H
