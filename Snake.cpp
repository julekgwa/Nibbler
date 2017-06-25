//
// Created by julekgwa on 2017/06/20.
//

#include "Snake.hpp"

Snake::Snake() {
    _dl_handle = dlopen("sdllib.so", RTLD_LAZY | RTLD_LOCAL);

    if (!_dl_handle)
        dlerror_wrapper();

    IList   *(*createList)(void);

    createList = (IList *(*)(void)) dlsym(_dl_handle,"createList");

    if (!createList)
        dlerror_wrapper();

    _snakes = createList();
    _maxHeight = _snakes->getHeight();
    _maxWidth = _snakes->getWidth();
    _minHeight = _snakes->getMinY();
    _minWidth = _snakes->getMinX();
    _snakes->addHead((_maxWidth - 2) / 2 - 15, _maxHeight / 2, 'o');
    _snakes->addHead((_maxWidth - 2) / 2 - 14, _maxHeight / 2, 'o');
    _snakes->addHead((_maxWidth - 2) / 2 - 13, _maxHeight / 2, 'o');
    _snakes->addHead((_maxWidth - 2) / 2 - 12, _maxHeight / 2, 'o');
    _snakes->addHead((_maxWidth - 2) / 2 - 11, _maxHeight / 2, 'o');
    _snakes->addHead((_maxWidth - 2) / 2 - 10, _maxHeight / 2, 'o');
    _snakes->addHead((_maxWidth - 2) / 2 - 9, _maxHeight / 2, 'o');
    _snakes->addHead((_maxWidth - 2) / 2 - 8, _maxHeight / 2, 'o');
    _snakes->addHead((_maxWidth - 2) / 2 - 7, _maxHeight / 2, 'o');
    _snakes->addHead((_maxWidth - 2) / 2 - 6, _maxHeight / 2, 'o');
    _snakes->addHead((_maxWidth - 2) / 2 - 5, _maxHeight / 2, 'o');
    _snakes->addHead((_maxWidth - 2) / 2 - 4, _maxHeight / 2, 'o');
    _snakes->addHead((_maxWidth - 2) / 2 - 3, _maxHeight / 2, 'o');
    _snakes->addHead((_maxWidth - 2) / 2 - 2, _maxHeight / 2, 'o');
    _snakes->addHead((_maxWidth - 2) / 2 - 1, _maxHeight / 2, 'o');
    _food = new Food;
    generateFood();
    _direction = RIGHT;
    _score = 0;
    _collision = false;
}

void    Snake::dlerror_wrapper(void)
{
    std::cerr << "Error: " << dlerror() << std::endl;
    exit(EXIT_FAILURE);
}

Snake::~Snake() {
    delete _food;

    void    (*deleteList)(IList *);

    deleteList = (void (*)(IList *)) dlsym(_dl_handle,"deleteList");

    deleteList(_snakes);
}

int Snake::getMove() {
    int    key = _snakes->getMove();

    if  (key != 'q')
        _direction = key;
    return key;
}

void Snake::wallCollision() {
    Piece snake = _snakes->getPiece(1);
    if (snake.xLoc >= _maxWidth || snake.yLoc >= _maxHeight || snake.xLoc < _minWidth || snake.yLoc < _minHeight) {
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
