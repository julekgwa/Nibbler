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
    List(int x, int y) throw (myYtooBig, myYtooSmall,myXtooBig,myXtooSmall);

    ~List();

    void removeTail();

    int length();

    Piece getPiece(int pos);

    void addHead(int, int, char);
    bool checkPos();
    Piece getOldTail();
    void printSnakePieces(Food *food);
    void displayScore(int _score, int _maxWidth, int _maxHeight);
    int     getWidth(void);
    int     getHeight(void);
    int     getMinWidth(void);
    int     getMinHeight(void);
    void    OST(int _score);
    int     getMove();

    class myYtooBig: public std::exception
    {
        public:
            myYtooBig(void);
            virtual ~myYtooBig() throw();
            virtual const char* what() const throw();
            myYtooBig(myYtooBig const &);
            myYtooBig   &operator=(myYtooBig const &);
    };

    class myYtooSmall: public std::exception
    {
    public:
        virtual const char* what() const throw();
        myYtooSmall(void);
        virtual ~myYtooSmall() throw();
        myYtooSmall(myYtooSmall const &);
        myYtooSmall   &operator=(myYtooSmall const &);
    };

    class myXtooBig: public std::exception
    {
    public:
        virtual const char* what() const throw();
        myXtooBig(void);
        virtual ~myXtooBig() throw();
        myXtooBig(myXtooBig const &);
        myXtooBig   &operator=(myXtooBig const &);
    };

    class myXtooSmall: public std::exception
    {
    public:
        virtual const char* what() const throw();
        myXtooSmall(void);
        virtual ~myXtooSmall() throw();
        myXtooSmall(myXtooSmall const &);
        myXtooSmall   &operator=(myXtooSmall const &);
    };

private:
    int _length;
    int height, width,_minHeight, _minWidth;
    int _direction;
    Piece *_head, *_tail;
    Piece _oldTail;
    WINDOW *_window;
    List();
    List    &operator=(List &);
    List(List &);
};

extern "C" {

    List    *createList(int x, int y);

    void    deleteList(List *list);

    void    test(void);

}


#endif //NIBBLER_NCURSESLIB_HPP
