//
// Created by Junius LEKGWARA on 2017/06/24.
//

#ifndef NIBBLER_STDLLIB_HPP
#define NIBBLER_STDLLIB_HPP

#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdlib.h>
#include <unistd.h>
#include "IList.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>


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
    int     getWidth(void);
    int     getHeight(void);
    void    OST(int _score);
    int     getMove();
    void draw(Piece piece);
    void drawFruit(void);
    void setTexture(SDL_Texture *);
    SDL_Texture *getTexture();
    Food *generateFood();
    int getMinX();
    int getMinY();
    SDL_bool test();
    void setFoodX(int x);

    void setFoodY(int y);

    int getFoodX();

    int getFoodY();

private:
    int _length;
    int _height, _width, _score;
    int _direction, _minX, _minY, _foodY, _foodX;
    Food *_food;
    Piece *_head, *_tail;
    Piece _oldTail;
    SDL_Surface *_background_surface;
    SDL_Surface *_food_background_surface;
    SDL_Texture *_food_background_texture;
    SDL_Texture *_background_texture;
    SDL_Window *_sdl_window;
    bool _quit, _eaten;
    const Uint8 *_keystate;
    SDL_Renderer *_renderer;
    SDL_Event _event;
    SDL_bool collision;
    SDL_Rect _rect, _food_rect;
    int rangeRandom(int min, int max);
};

extern "C" {

List    *createList(void);

void    deleteList(List *list);

}


#endif //NIBBLER_STDLLIB_HPP
