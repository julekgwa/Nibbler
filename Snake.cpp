//
// Created by julekgwa on 2017/06/20.
//

#include "Snake.hpp"
Snake::Snake(WINDOW *win) {
    _currentWin = win;
    getmaxyx(_currentWin, _maxHeight, _maxWidth);
    _direction = RIGHT;
    _snakes.insertHead((_maxWidth - 2) / 2 - 4, _maxHeight / 2, 'o');
   _snakes.insertHead((_maxWidth - 2) / 2 - 3,  _maxHeight / 2, 'o');
    _snakes.insertHead((_maxWidth - 2) / 2 - 2,  _maxHeight / 2, 'o');
    _snakes.insertHead((_maxWidth - 2) / 2 - 1,  _maxHeight / 2, 'o');
    keypad(_currentWin, true);
}

Snake::~Snake() {

}

int Snake::getMove() {
    int key = wgetch(_currentWin);
    switch (key) {
        case KEY_UP:
            _direction = UP;
            break;
        case KEY_DOWN:
            _direction = DOWN;
            break;
        case KEY_LEFT:
            _direction = LEFT;
            break;
        case KEY_RIGHT:
            _direction = RIGHT;
            break;
    }
    return key;
}

void Snake::wallCollision() {
    Piece snake = _snakes.getPiece(1);
    if (snake.xLoc == _maxWidth || snake.yLoc == _maxHeight || snake.xLoc < 0 || snake.yLoc < 0)
        _collision = true;
}

void Snake::OST() {
    // used for displaying game lives and scores
}

void Snake::moveSnake() {
    Piece snake = _snakes.getPiece(1);
    int x = snake.xLoc, y = snake.yLoc;
    char character = snake.character;
    if (_direction == UP) {
        y--;
    } else if (_direction == DOWN) {
        y++;
    } else if (_direction == LEFT) {
        x--;
    } else {
        x++;
    }
    _snakes.insertHead(x, y, snake.character);
    if (_snakes.length() > 1)
        _snakes.removeTail();
    for (int i = 1; i <= _snakes.length(); ++i) {
        snake = _snakes.getPiece(i);
        if (i > 1)
            character = '#';
        mvaddch(snake.yLoc, snake.xLoc, character);
        refresh();
    }
}

bool Snake::getCollision() {
    return _collision;
}