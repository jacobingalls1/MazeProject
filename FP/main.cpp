/* CSCI 261: Final Project: Maze game
 *
 * Author: Jacob Ingalls
 *
 *    The user is promted to guess a random number between the LOW bound and
 *    HIGH bound and given clues.
 */
#include <iostream>
#include "maze.h"
#include <ctime>
#include <vector>
#include <cmath>
using namespace std;


#include <SFML/Graphics.hpp>
using namespace sf;

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

int main() {
    srand(time(NULL));
    cout << "Hello! Please input the side length of your maze" << endl;
    int mazeX(getInt(4, 30));
    cout << "Select your difficulty" << endl;
    const int UPDATE_RATE(getInt(1, 10));
    cout << "Okay, good choice, you'll be the blue square."
            " Get to the bottom right corner while avoiding the red enemies!" << endl;
    const int DRAW_SCALE = 1000 / mazeX;
    const string winning("You have conquered the maze!"), loss("You have been defeated!");
    Maze maze(mazeX, mazeX);
    RenderWindow window(VideoMode(DRAW_SCALE * mazeX, DRAW_SCALE * mazeX), "Labyrinth");
    Point playerPos(1, 1);

    int stepCount = 0;

    Font arial;
    arial.loadFromFile("ARMS.ttf");
    if (!arial.loadFromFile("ARMS.ttf")) {
        return -1;
    }

    while (window.isOpen()) {

        // WORKS
        window.clear(Color::Black);
        vector<vector<bool>> drawMaze = maze.getMaze();
        for (int i = 0; i < mazeX; i++) {
            for (int j = 0; j < mazeX; j++) {
                Point ij(i, j);
                RectangleShape rect;
                rect.setPosition(DRAW_SCALE * i, DRAW_SCALE * j);
                rect.setSize(Vector2f(DRAW_SCALE, DRAW_SCALE));
                if (maze.mazeAt(ij)) {
                    rect.setFillColor(Color(200, 200, 200));
                } else {
                    rect.setFillColor(Color(100, 100, 100));
                }
                if (maze.getPlayer()[0] == i and maze.getPlayer()[1] == j) {
                    rect.setFillColor(Color(0, 0, 255));
                }
                if (maze.enemyAt(ij)) {
                    rect.setFillColor(Color(255, 0, 0));
                }
                if (maze.end[0] == ij.x and maze.end[1] == ij.y) {
                    rect.setFillColor(Color(0, 255, 0));
                }
                window.draw(rect);
            }

        }


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

        //WORKS
        if ((stepCount) % (45000 / (mazeX * mazeX) * UPDATE_RATE) == 0) {
            maze.enemyMove();
        }

        //WORKS
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            } else if (event.type == Event::KeyPressed) {
                switch (event.key.code) {
                    case Keyboard::Left:
                    case Keyboard::A:
                        maze.left();
                        break;
                    case Keyboard::Right:
                    case Keyboard::D:
                        maze.right();
                        break;
                    case Keyboard::Up:
                    case Keyboard::W:
                        maze.up();
                        break;
                    case Keyboard::Down:
                    case Keyboard::S:
                        maze.down();
                        break;
                    case Keyboard::Escape:
                    case Keyboard::Q:
                        window.close();
                        break;
                }
            }
        }
    }
    return EXIT_SUCCESS;
}