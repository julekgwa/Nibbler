//
// Created by julekgwa on 2017/06/20.
//

#ifndef NIBBLER_PIECE_HPP
#define NIBBLER_PIECE_HPP
typedef struct Piece {
    struct Piece *next;
    int xLoc, yLoc;
    char character;
} Piece;
#endif //NIBBLER_PIECE_HPP
