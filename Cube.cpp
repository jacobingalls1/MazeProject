#include <cmath>
#include "Cube.h"
using namespace std;

const float FOV = 60;

Cube::Cube(Vector2i pos, Color color) {
    this->pos = Vector2f(pos.x, pos.y);
    this->color = color;
}

float angle(Vector2f v) {
    return (float)(180 / (2 * 3.141592) * (1 / (tan(v.x / v.y))));
}

float distance(Vector2f v1, Vector2f v2) {
    return (float)sqrt(pow(v1.x - v2.x, 2) + pow(v1.y - v2.y, 2));
}

vector<Square> Cube::getSides(Point player) {
    vector<Square> final;
    Vector2f diff(player.pos() - pos);
    for (Vector2f v : vector<Vector2f>({Vector2f(1, 0), Vector2f(-1, 0), Vector2f(0, 1), Vector2f(0, -1)})) {
        if (distance(pos, player.pos()) > distance(pos + v, player.pos())) {
            Square s;
            s.pos = Vector2f(diff.x + v.x / 2, diff.y + v.y / 2);
            s.color = color;
            s.dist = distance(player.pos(), s.pos);
            s.xOrient = v.x != 0;
            final.push_back(s);
        }
    }
    return final;
}

vector<Vector2f> Square::getCorners() {
    vector<Vector2f> final;
    if (xOrient) {
        final.push_back(pos + Vector2f(0, .5));
        final.push_back(pos + Vector2f(0, -0.5));
    } else {
        final.push_back(pos + Vector2f(.5, 0));
        final.push_back(pos + Vector2f(-0.5, 0));
    }
    return final;
}

bool pVis(Point player, Vector2f target) {
    float ang = angle(target);
    return    abs(player.getAngle() -  ang)        < FOV
           || abs(player.getAngle() - (ang + 360)) < FOV
           || abs(player.getAngle() - (ang - 360)) < FOV;
}

bool Square::visible(Point player) {
    for (Vector2f v : this->getCorners()) {
        if (pVis(player, v)) return true;
    }
    return false;
}



vector<Vertex*> Cube::getDrawings(Point player, float screenSide) {
    vector<Vertex*> final;
    vector<Square> sides(getSides(player));

    while (!sides.empty()) {
        int in = 0;
        float max = sides[0].dist;
        for (int i = 0; i < sides.size(); i++) {
            if (sides[i].dist > max) {
                max = sides[i].dist;
                in = i;
            }
        }
        Square sq = sides[in];
        sides.erase(sides.begin() + in);
        if (sq.visible(player)) {
            vector<Vector2f> corners(sq.getCorners());
            Vector2f screen(player.getAngle() - FOV, player.getAngle() + FOV);
            Vector2f edges(player.getAngle() - angle(corners[0]), player.getAngle() - angle(corners[1]));
            float corner1 = angle(Vector2f(distance(player.pos(), corners[0]), .5));
            float corner2 = angle(Vector2f(distance(player.pos(), corners[1]), .5));
//            if (corner1 > screenSide / 2) corner1 = screenSide / 2;
//            if (corner2 > screenSide / 2) corner2 = screenSide / 2;
            edges.x = screenSide * edges.x / (4 * FOV);
            edges.y = screenSide * edges.y / (4 * FOV);
            sf::Vertex vertices[] =
                    {
                            Vertex(Vector2f(edges.x, screenSide / 2 + corner1), color),
                            Vertex(Vector2f(edges.x, screenSide / 2 - corner1), color),
                            Vertex(Vector2f(edges.y, screenSide / 2 - corner2), color),
                            Vertex(Vector2f(edges.y, screenSide / 2 + corner2), color)
                    };
            final.push_back(vertices);
        }
    }
    return final;
}