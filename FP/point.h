#ifndef CHESS_POINT_H
#define CHESS_POINT_H
#include <vector>
#include <iostream>

using namespace std;


class Point {
public:
    int x, y;
    Point(int xPos, int yPos);
    bool operator==(Point);
    Point add(Point toAdd);
    Point vectAdd(vector<int> toAdd);
    bool verify();
    bool isIn(vector<Point>);
};


#endif //CHESS_POINT_H
