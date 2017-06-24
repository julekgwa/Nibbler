
#ifndef NIBBLER_ListLIB_HPP
#define NIBBLER_ListLIB_HPP

#include <ncurses.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdlib.h>
#include <unistd.h>

typedef struct Piece
{
    struct Piece *next;
    int xLoc, yLoc;
    char character;
} Piece;

typedef struct Food
{
    int xLoc, yLoc;
    char character;
} Food;

WINDOW *init();

class List
{
  public:
    List();
    List(List &rhs);
    List &operator=(List &rhs);
    ~List();
    void removeTail();
    int length();
    Piece getPiece(int pos);
    void addHead(int, int, char);
    bool checkPos();
    Piece getOldTail();
    int getHeight();
    int getWidth();
    void printSnakePieces(Food *food, List snakes);
    void displayScore(int _score, int _maxWidth, int _maxHeight);
    WINDOW *getWindow(void);
    void OST(int _score);

  private:
    int _length;
    int height, width;
    Piece *_head, *_tail;
    Piece _oldTail;
    WINDOW *_window;
};

#endif
