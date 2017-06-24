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

class Snake {
public:
    Snake();

    ~Snake();

    bool getCollision(void);

    int getMove(void);

    void moveSnake(void);

    void generateFood(void);

    void wallCollision(void);

    void displayScore(void);

    void OST(void);


private:
    int _maxHeight, _maxWidth, _direction, _score;
    bool _collision;
    List *_snakes;
    Food *_food;
};


#endif //NIBBLER_SNAKE_HPP
