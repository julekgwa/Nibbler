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

typedef struct Piece {
    struct Piece *next;
    int xLoc, yLoc;
    char character;
} Piece;

typedef struct Food {
    int xLoc, yLoc;
    char character;
}Food;

WINDOW *init();

class List {
public:
    List();

    ~List();

    void removeTail();

    int length();

    Piece getPiece(int pos);

    void addHead(int, int, char);
    bool checkPos();
    Piece getOldTail();
    void printSnakePieces(Food *food, List snakes);
    void displayScore(int _score, int _maxWidth, int _maxHeight);

private:
    int _length;
    Piece *_head, *_tail;
    Piece _oldTail;
};


#endif //NIBBLER_NCURSESLIB_HPP
