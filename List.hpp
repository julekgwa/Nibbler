//
// Created by julekgwa on 2017/06/20.
//

#ifndef NIBBLER_LIST_HPP
#define NIBBLER_LIST_HPP

#include "Piece.hpp"
#include <iostream>
class List {
public:
    List();

    ~List();

    void removeTail();

    int length();

    Piece getPiece(int pos);

    void addHead(int, int, char);

private:
    int _length;
    Piece *_head, *_tail;
};


#endif //NIBBLER_LIST_HPP
