//
// Created by julekgwa on 2017/06/20.
//

#ifndef NIBBLER_NCURSESLIB_HPP
#define NIBBLER_NCURSESLIB_HPP

#include <ncurses.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdlib.h>
#include <unistd.h>
#include "IList.hpp"


class List : public IList {
public:
    List();

    ~List();

    void removeTail();

    int length();

    Piece getPiece(int pos);

    void addHead(int, int, char);
    bool checkPos();
    Piece getOldTail();
    void printSnakePieces(Food *food);
    void displayScore(int _score, int _maxWidth, int _maxHeight);
    WINDOW *getWindow(void);
    int     getWidth(void);
    int     getHeight(void);
    void    OST(int _score);
    int     getMove();

private:
    int _length;
    int height, width;
    int _direction;
    Piece *_head, *_tail;
    Piece _oldTail;
    WINDOW *_window;
};

extern "C" {

    List    *createList(void);

    void    deleteList(List *list);

    void    test(void);

}


#endif //NIBBLER_NCURSESLIB_HPP