//
// Created by julekgwa on 2017/06/20.
//

#ifndef NIBBLER_SNAKE_HPP
#define NIBBLER_SNAKE_HPP

#include <iostream>
#include <ncurses.h>
#include <unistd.h>
//#include "ncurseslib.hpp"
#include "IList.hpp"
#include <dlfcn.h>
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

    void dlerror_wrapper(void);


private:
    int _maxHeight, _maxWidth, _minHeight,_minWidth, _direction, _score;
    bool _collision;
    IList   *_snakes;
    Food *_food;
    void    *_dl_handle;
};


#endif //NIBBLER_SNAKE_HPP
