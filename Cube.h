#ifndef SFML_TEMPLATE_CUBE_H
#define SFML_TEMPLATE_CUBE_H

#include <vector>
#include "point.h"
using namespace std;

#include <SFML/Graphics.hpp>
using namespace sf;


struct Square {
    Vector2f pos = Vector2f(0, 0);
    Color color;
    float dist;
    bool xOrient;
    bool visible(Point player);
    vector<Vector2f> getCorners();
};

class Cube {
public:
    Vector2f pos;
    Color color;
    Cube(Vector2i pos, Color color);
    vector<Square> getSides(Point player);
    vector<Vertex*> getDrawings(Point player, float screen);
};


#endif //SFML_TEMPLATE_CUBE_H
