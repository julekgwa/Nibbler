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
#include "List.hpp"

class Snake {
public:
    Snake(WINDOW *win);

    ~Snake();

    bool getCollision(void);

    int getMove(void);

    void moveSnake(void);

    void wallCollision(void);

    void OST(void);

private:
    int _maxHeight, _maxWidth, _direction;
    WINDOW *_currentWin;
    bool _collision;
    List _snakes;
};


#endif //NIBBLER_SNAKE_HPP
