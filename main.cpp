//
// Created by julekgwa on 2017/06/20.
//

#include "List.hpp"
#include <iostream>
#include "Snake.hpp"
#include <ncurses.h>
#include "ncurseslib.hpp"

int main() {
    WINDOW *window = init();
    Snake *snake = new Snake(window);
    while (snake->getMove() != 'q' && !snake->getCollision()) {
        //clear();
        snake->moveSnake();
        snake->wallCollision();
        snake->OST();
    }
    endwin();
    return 0;
}