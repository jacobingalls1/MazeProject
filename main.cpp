/* CSCI 261: Final Project: Maze game
 *
 * Author: Jacob Ingalls
 *
 *    The user is promted to guess a random number between the LOW bound and
 *    HIGH bound and given clues.
 */
#include <iostream>
#include "maze.h"
#include "cube.h"
#include <ctime>
#include <vector>
#include <cmath>
#include <cstdlib>
using namespace std;


#include <SFML/Graphics.hpp>
using namespace sf;

const Color wallC(100, 100, 100), floorC(200, 200, 200), playerC(0, 0, 255), enemyC(255, 0, 0), endC(0, 255, 0);

int getInt(int min, int max) {
    int user = min - 1;
    while (!(min <= user and user <= max)) {
        if (user == -1000) {
            cout << "Limits overridden... don't break anything" << endl;
            cin >> user;
            break;
        }
        cout << "Input an integer between " << min << " and " << max << " inclusive" << endl;
        cin >> user;
    }
    return user;
}

int ran() {
    return rand() % 15;
}

int main() {
//    srand(time(NULL));
//    cout << "Hello! Please input the side length of your maze" << endl;
//    int mazeX(getInt(4, 30));
//    cout << "Select your difficulty" << endl;
//    const int UPDATE_RATE(getInt(1, 10));
//    cout << "Okay, good choice, you'll be the blue square."
//            " Get to the bottom right corner while avoiding the red enemies!" << endl;
    int mazeX = 15;
    int UPDATE_RATE = 5;
    const int SCREEN_BASE = 1000, DRAW_SCALE = SCREEN_BASE / mazeX, SCREEN_SIZE = DRAW_SCALE * mazeX;
    const string winning("You have conquered the maze!"), loss("You have been defeated!");
    Maze maze(mazeX, mazeX);
    RenderWindow window(VideoMode(DRAW_SCALE * mazeX, DRAW_SCALE * mazeX), "Labyrinth");
    RenderWindow laby(VideoMode(SCREEN_SIZE, SCREEN_SIZE), "MAZE");
    laby.setPosition(Vector2i(2000, 0));
    window.setMouseCursorVisible(false);
    Point player(1, 1);

    vector<Cube> cubes;
    cubes.push_back(Cube(Vector2i(ran(), ran()), Color::Red));
    cubes.push_back(Cube(Vector2i(ran(), ran()), Color::Green));
    cubes.push_back(Cube(Vector2i(ran(), ran()), Color::White));
    cubes.push_back(Cube(Vector2i(ran(), ran()), Color::Blue));

    int stepCount = 0;

    Font arial;
    arial.loadFromFile("ARMS.ttf");
    if (!arial.loadFromFile("ARMS.ttf")) {
        return -1;
    }

    bool l = false, r = false, u = false, d = false;

    while (window.isOpen()) {
//        cout << maze.playerP().x << " " << maze.playerP().y << endl;
        window.clear(floorC);
        RectangleShape rect;
        rect.setPosition(0, 0);
        rect.setFillColor(Color::Cyan);
        rect.setSize(Vector2f(SCREEN_SIZE, SCREEN_SIZE / 2));
        window.draw(rect);
        for (Cube c : cubes) {
            for (Vertex *vert : c.getDrawings(maze.playerP(), SCREEN_SIZE)) {
                window.draw(vert, 4, sf::Quads);
            }
        }
        int screenSide(SCREEN_SIZE);
        window.display();
        window.display();

        laby.clear(Color::Black);
        vector<vector<bool>> drawMaze = maze.getMaze();
        for (int i = 0; i < mazeX; i++) {
            for (int j = 0; j < mazeX; j++) {
                Point ij(i, j);
                RectangleShape rect;
                rect.setPosition(DRAW_SCALE * i, DRAW_SCALE * j);
                rect.setSize(Vector2f(DRAW_SCALE, DRAW_SCALE));
                if (maze.mazeAt(ij)) {
                    rect.setFillColor(floorC);
                } else {
                    rect.setFillColor(wallC);
                }
                if (maze.enemyAt(ij)) {
                    rect.setFillColor(enemyC);
                }
                if (maze.end.xI() == ij.xI() and maze.end.yI() == ij.yI()) {
                    rect.setFillColor(endC);
                }
                laby.draw(rect);
            }

        }
        vector<Vector2i> vec = maze.los();
        for (int i = 0; i < vec.size(); i++) {
            Vector2i v = vec[i];
            RectangleShape rect;
            rect.setPosition(DRAW_SCALE * v.x, DRAW_SCALE * v.y);
            rect.setSize(Vector2f(DRAW_SCALE, DRAW_SCALE));
            rect.setFillColor(Color::Black);
            laby.draw(rect);
        }
        RectangleShape rect2;
        Vector2f playerPos(maze.getPlayerF().x * DRAW_SCALE, maze.getPlayerF().y * DRAW_SCALE);
        rect2.setPosition(playerPos);
        rect2.setSize(Vector2f(DRAW_SCALE / 5, DRAW_SCALE / 5));
        rect2.setFillColor(playerC);
        laby.draw(rect2);
        rect2.setPosition(playerPos - (float)10 * maze.downDir());
        rect2.setFillColor(Color::Magenta);
        laby.draw(rect2);
        for (Cube c : cubes) {
            RectangleShape rect;
            rect.setPosition(Vector2f(c.pos.x * DRAW_SCALE, c.pos.y * DRAW_SCALE));
            rect.setSize(Vector2f(DRAW_SCALE, DRAW_SCALE));
            rect.setFillColor(c.color);
            laby.draw(rect);
        }

        laby.display();



        // WORKS
        if (maze.win) {
            window.clear(Color::Blue);
            Text text(winning, arial);
            Text exit("Press q, esc, or just close the window to leave.", arial);
            text.setCharacterSize(35);
            exit.setCharacterSize(25);
            text.setFillColor(Color::White);
            exit.setFillColor(Color::White);
            text.setPosition(65 + 50 * (1 + sin(stepCount / 200.0)), 100 + 300 * (1 + cos(stepCount / 500.0)));
            exit.setPosition(75, 800);
            window.draw(text);
            window.draw(exit);
        } else if (maze.dead) {
            window.clear(Color::Red);
            Text text(loss, arial);
            Text exit("Press q, esc, or just close the window to leave.", arial);
            text.setCharacterSize(40);
            exit.setCharacterSize(25);
            text.setFillColor(Color::Black);
            exit.setFillColor(Color::Black);
            text.setPosition(90 + 50 * (1 + sin(stepCount / 200.0)), 100 + 300 * (1 + cos(stepCount / 500.0)));
            exit.setPosition(75, 800);
            window.draw(text);
            window.draw(exit);
        }
        window.display();
        if (stepCount++ > 100000) {
            stepCount = 0;
        }

        if ((stepCount) % (45000 / (mazeX * mazeX) * UPDATE_RATE) == 0) {
            maze.enemyMove();
        }

        if (u) maze.up();
        if (d) maze.down();
        if (l) maze.left();
        if (r) maze.right();

        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
                laby.close();
            } else if (event.type == Event::KeyPressed) {
                switch (event.key.code) {
                    case Keyboard::Left:
                    case Keyboard::A:
                        l = true;
                        break;
                    case Keyboard::Right:
                    case Keyboard::D:
                        r = true;
                        break;
                    case Keyboard::Up:
                    case Keyboard::W:
                        u = true;
                        break;
                    case Keyboard::Down:
                    case Keyboard::S:
                        d = true;
                        break;
                    case Keyboard::Escape:
                    case Keyboard::Q:
                        window.close();
                        break;
                }
            } else if (event.type == Event::KeyReleased) {
                switch (event.key.code) {
                    case Keyboard::Left:
                    case Keyboard::A:
                        l = false;
                        break;
                    case Keyboard::Right:
                    case Keyboard::D:
                        r = false;
                        break;
                    case Keyboard::Up:
                    case Keyboard::W:
                        u = false;
                        break;
                    case Keyboard::Down:
                    case Keyboard::S:
                        d = false;
                        break;
                    case Keyboard::Escape:
                    case Keyboard::Q:
                        window.close();
                        laby.close();
                        break;
                }
            }
        }
        Vector2i mousePos = Mouse::getPosition(window);
        Mouse::setPosition(Vector2i(SCREEN_SIZE / 2, SCREEN_SIZE / 2), window);
        maze.update(mousePos.x - SCREEN_SIZE / 2);
        player.turn(mousePos.x - SCREEN_SIZE / 2);
    }
    return EXIT_SUCCESS;
}