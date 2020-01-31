#include "point.h"

Point::Point(int xPos, int yPos) {
    x = xPos;
    y = yPos;
}

bool Point::operator==(const Point target) {
    return x == target.x and y == target.y;
}

Point Point::add(Point toAdd) {
    return Point(x + toAdd.x, y + toAdd.y);
}

Point Point::vectAdd(vector<int> toAdd) {
    return Point(x + toAdd[0], y + toAdd[1]);
}

bool Point::verify() {
    return x > 0 and y > 0;
}

bool Point::isIn(vector<Point> search) {
    for (int i = 0; i < search.size(); i++) {
        if (this->x == search[i].x and this->y == search[i].y) {
            return true;
        }
    }
    return false;
}
