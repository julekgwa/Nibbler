//
// Created by julekgwa on 2017/06/20.
//

#include "Snake.hpp"

Snake::Snake() {
    _snakes = createList();
    _maxHeight = _snakes->getHeight();
    _maxWidth = _snakes->getWidth();
    _snakes->addHead((_maxWidth - 2) / 2 - 7, _maxHeight / 2, 'o');
    _snakes->addHead((_maxWidth - 2) / 2 - 6, _maxHeight / 2, 'o');
    _snakes->addHead((_maxWidth - 2) / 2 - 5, _maxHeight / 2, 'o');
    _snakes->addHead((_maxWidth - 2) / 2 - 4, _maxHeight / 2, 'o');
    _snakes->addHead((_maxWidth - 2) / 2 - 3, _maxHeight / 2, 'o');
    _snakes->addHead((_maxWidth - 2) / 2 - 2, _maxHeight / 2, 'o');
    _snakes->addHead((_maxWidth - 2) / 2 - 1, _maxHeight / 2, 'o');
    keypad(_snakes->getWindow(), true);
    _food = new Food;
    generateFood();
    _direction = RIGHT;
    _score = 0;
    _collision = false;
}

Snake::~Snake() {
    delete _food;
    endwin();
}

int Snake::getMove() {
    int key = wgetch(_snakes->getWindow());
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
    Piece snake = _snakes->getPiece(1);
    if (snake.xLoc == _maxWidth || snake.yLoc == _maxHeight || snake.xLoc == 1 || snake.yLoc == 1) {
        _collision = true;
        return;
    }
    _collision = _snakes->checkPos();
}

void Snake::displayScore() {
    _snakes->displayScore(_score, _maxWidth, _maxHeight);
    return;
}

void Snake::OST() {
    // used for displaying game lives and scores
//    mvprintw(0, 0, "Max w: %d | Max h: %d | F x: %d, F y: %d", _maxWidth, _maxHeight, _food->xLoc, _food->yLoc);
//    mvprintw(_maxHeight + 1, 2, "score: %d", _score);
//    refresh();
    _snakes->OST(_score);
}

void Snake::generateFood() {
    srand(time(NULL)); // Seed the time
    int y = rand() % ((int) (_maxHeight - 2 + 1) + 2);
    int x = rand() % ((int) (_maxWidth - 2 + 1) + 2);
    if (y >= _maxHeight)
        y = _maxHeight - 2;
    if (y <= 1) {
        y = 3;
    }
    if (x >= _maxWidth)
        x = _maxWidth - 2;
    if (x <= 1)
        x = 3;
    _food->xLoc = x;
    _food->yLoc = y;
    _food->character = 'x';
    
    /*while ((_food->xLoc > _maxWidth || _food->xLoc <= 1) || (_food->yLoc > _maxHeight || _food->yLoc <= 1))
    {
        _food->xLoc = (rand() % (int) (_maxWidth - 5));
        _food->yLoc = (rand() % (int) (_maxHeight - 5));
    }*/
}

// we'll move the snake by removing the tail and adding a new head each time
// giving the head new location depending on the key press
// see this answer on stackoverflow https://stackoverflow.com/questions/27906211/making-snake-game-in-cpp-movement-of-snake
void Snake::moveSnake() {
    Piece snake = _snakes->getPiece(1);
    int x = snake.xLoc, y = snake.yLoc;
    if (_direction == UP) {
        y--;
    } else if (_direction == DOWN) {
        y++;
    } else if (_direction == LEFT) {
        x--;
    } else {
        x++;
    }
    _snakes->addHead(x, y, snake.character);
    if (_food->xLoc == x && _food->yLoc == y) {
        generateFood();
        _score++;
    } else {
        _snakes->removeTail();
    }
    _snakes->printSnakePieces(_food);
}

bool Snake::getCollision() {
    return _collision;
}
