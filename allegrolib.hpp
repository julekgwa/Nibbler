//
// Created by julekgwa on 2017/06/26.
//

#ifndef NIBBLER_ALLEGROLIB_HPP
#define NIBBLER_ALLEGROLIB_HPP

#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdlib.h>
#include <unistd.h>
#include "allegro5/allegro.h"
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "IList.hpp"

class List : public IList {
public:
    List(int w, int h);

    ~List();

    void removeTail();

    int length();

    Piece getPiece(int pos);

    void addHead(int, int, char);

    bool checkPos();

    Piece getOldTail();

    void printSnakePieces(Food *food);

    void displayScore(int score, int maxWidth, int maxHeight);

    int getWidth(void);

    int getHeight(void);

    int getMinX();

    int getMinY();

    void OST(int score);

    int getMove();

private:
    int _length;
    int _winHeight, _winWidth, _minX, _minY, _foodY, _foodX;
    int _direction;
    Piece *_head, *_tail;
    Piece _oldTail;
    int _fps;
    bool _redraw;
    Food *_food;
    ALLEGRO_DISPLAY *_display;
    ALLEGRO_EVENT_QUEUE *_event_queue;
    ALLEGRO_EVENT _event;
    ALLEGRO_TIMER *_timer;
    ALLEGRO_BITMAP *_bitmap;
    List();
};

extern "C" {

List *createList(void);

void deleteList(List *list);

}


#endif //NIBBLER_ALLEGROLIB_HPP
