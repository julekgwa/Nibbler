//
// Created by Goitsemang SETSIBA on 2017/06/24.
//

#ifndef NIBBLER_ILIST_H
#define NIBBLER_ILIST_H

#define UP 1
#define DOWN 2
#define RIGHT 4
#define LEFT 3

typedef struct Piece {
    struct Piece *next;
    int xLoc, yLoc;
    char character;
} Piece;

typedef struct Food {
    int xLoc, yLoc;
    char character;
}Food;

class IList{

public:
    IList(){};
    virtual ~IList(){};
    virtual void removeTail() = 0;

    virtual int length() = 0;

    virtual Piece getPiece(int pos) = 0;

    virtual void addHead(int, int, char) = 0;
    virtual bool checkPos() = 0;
    virtual Piece getOldTail() = 0;
    virtual void printSnakePieces(Food *food) = 0;
    virtual void displayScore(int _score, int _maxWidth, int _maxHeight) = 0;
    virtual int     getWidth(void) = 0;
    virtual int     getHeight(void) = 0;
    virtual void    OST(int _score) = 0;
    virtual int     getMove() = 0;
    virtual int getMinX() = 0;
    virtual int getMinY() = 0;
    virtual Food *generateFood() = 0;
};

#endif //NIBBLER_ILIST_H
