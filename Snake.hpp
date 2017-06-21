//
// Created by julekgwa on 2017/06/20.
//

#ifndef NIBBLER_SNAKE_HPP
#define NIBBLER_SNAKE_HPP
#define UP 1
#define DOWN 2
#define RIGHT 4
#define LEFT 3

#include <iostream>
#include <ncurses.h>
#include <unistd.h>
#include "ncurseslib.hpp"
#include <cstdlib>
#include <stdlib.h>

class Snake {
public:
    Snake(WINDOW *);

    ~Snake();

    bool getCollision(void);

    int getMove(void);

    void moveSnake(void);

    void generateFood(void);

    void wallCollision(void);

    void OST(void);

//    void init();

private:
    int _maxHeight, _maxWidth, _direction, _score;
    WINDOW *_currentWin;
    bool _collision;
    List _snakes;
    Food *_food;
};


#endif //NIBBLER_SNAKE_HPP
