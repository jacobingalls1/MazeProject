#include "point.h"

const int MAX_ANGLE = 10000;

Point::Point(float xPos, float yPos, int facing) {
    x = xPos;
    y = yPos;
    this->facing = facing;
}

Point::Point(Vector2f pos, int facing) {
    x = pos.x;
    y = pos.y;
    this->facing = facing;
}
Point::Point(Vector2i pos, int facing) {
    x = pos.x;
    y = pos.y;
    this->facing = facing;
}

int Point::xI() {
    return (int)x;
}

float Point::xF() {
    return x;
}

int Point::yI() {
    return (int)y;
}

float Point::yF() {
    return y;
}

float Point::getAngle() {
    return 360 * facing / MAX_ANGLE;
}

Vector2f Point::pos() {
    return Vector2f(x, y);
}


bool Point::operator==(const Point target) {
    return (int)x == (int)target.x and (int)y == (int)target.y;
}

void Point::add(Point toAdd) {
    x += toAdd.x;
    y += toAdd.y;
    facing += toAdd.facing;
}

Point Point::vectAdd(vector<int> toAdd) {
    return Point(x + toAdd[0], y + toAdd[1]);
}

Point Point::vectAdd(Vector2f toAdd) {
    return Point(x + toAdd.x, y + toAdd.y);
}

bool Point::verify() {
    return x > 0 and y > 0;
}

void Point::turn(int amt) {
    facing += amt;
    facing %= MAX_ANGLE;
    while (facing < 0) {
        facing += MAX_ANGLE;
    }
}

bool Point::isIn(vector<Point> search) {
    for (int i = 0; i < search.size(); i++) {
        if (this->x == search[i].x and this->y == search[i].y) {
            return true;
        }
    }
    return false;
}
