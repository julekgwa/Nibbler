//
// Created by julekgwa on 2017/06/20.
//

#include "List.hpp"
#include <iostream>
#include "Snake.hpp"
#include <ncurses.h>

int main() {
    initscr();
    int height, width, starty, startx;
    getmaxyx(stdscr, height, width);
    curs_set(0);
    starty = (height - (height - 2)) / 2; /* Calculating for a center placement */
    startx = (width - (width - 2)) / 2;
    height -= 2;
    width -= 2;
    halfdelay(1);
    WINDOW *win = newwin(height, width, starty, startx);
    refresh();
    box(win, 0, 0);
    wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
    wrefresh(win);
    Snake *snake = new Snake(win);
    while (snake->getMove() != 'x' && !snake->getCollision()) {
        clear();
        snake->moveSnake();
        snake->wallCollision();
        //wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
        snake->OST();
    }
    endwin();
    return 0;
}