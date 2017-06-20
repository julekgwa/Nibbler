//
// Created by julekgwa on 2017/06/20.
//

#include "Snake.hpp"
Snake::Snake(WINDOW *win) {
    _currentWin = win;
    getmaxyx(_currentWin, _maxHeight, _maxWidth);
    _direction = RIGHT;
    this->_collision = false;
    _snakes.addHead((_maxWidth - 2) / 2 - 7, _maxHeight / 2, 'o');
    _snakes.addHead((_maxWidth - 2) / 2 - 6, _maxHeight / 2, 'o');
    _snakes.addHead((_maxWidth - 2) / 2 - 5, _maxHeight / 2, 'o');
    _snakes.addHead((_maxWidth - 2) / 2 - 4, _maxHeight / 2, 'o');
   _snakes.addHead((_maxWidth - 2) / 2 - 3,  _maxHeight / 2, 'o');
    _snakes.addHead((_maxWidth - 2) / 2 - 2,  _maxHeight / 2, 'o');
    _snakes.addHead((_maxWidth - 2) / 2 - 1,  _maxHeight / 2, 'o');
    keypad(_currentWin, true);
    generateFood();
    _score = 0;
    _collision = false;
}

Snake::~Snake() {

}

int Snake::getMove() {
    int key = wgetch(_currentWin);
    switch (key) {
        case KEY_UP:
            if (_direction != DOWN)
                _direction = UP;
            break;
        case KEY_DOWN:
            if (_direction != UP)
            _direction = DOWN;
            break;
        case KEY_LEFT:
            if (_direction != RIGHT)
            _direction = LEFT;
            break;
        case KEY_RIGHT:
            if (_direction != LEFT)
            _direction = RIGHT;
            break;
    }
    return key;
}

void Snake::wallCollision() {
    Piece snake = _snakes.getPiece(1);
    if (snake.xLoc == _maxWidth || snake.yLoc == _maxHeight  || snake.xLoc == 1 || snake.yLoc == 1)
    {
        _collision = true;
        return ;
    }
    _collision = _snakes.checkPos();
}

void Snake::OST() {
    // used for displaying game lives and scores
//    mvprintw(_maxWidth, 0, "--------------------");
    mvprintw(_maxHeight + 1, 2, "score: %d", _score);
    refresh();
}

void Snake::generateFood() {
    _food = new Food;
    _food->xLoc = (rand() % (int) (_maxWidth - 5));
    _food->yLoc = (rand() % (int) (_maxHeight - 5));
    _food->character = 'x';
}


// we'll move the snake by removing the tail and adding a new head each time
// giving the head new location depending on the key press
// see this answer on stackoverflow https://stackoverflow.com/questions/27906211/making-snake-game-in-cpp-movement-of-snake
void Snake::moveSnake() {
    Piece snake = _snakes.getPiece(1);
    Piece tail;
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
    _snakes.addHead(x, y, snake.character);
    if (_food->xLoc == x && _food->yLoc == y) {
        generateFood();
        _score++;
    } else {
        _snakes.removeTail();
    }
    mvaddch(_food->yLoc, _food->xLoc, _food->character);
    tail = _snakes.getOldTail();
    mvaddch(tail.yLoc, tail.xLoc, ' ');
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