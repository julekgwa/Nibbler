//
// Created by julekgwa on 2017/06/20.
//

#include "Snake.hpp"

int main() {
    Snake *snake = new Snake();
    while (snake->getMove() != 'q' && !snake->getCollision()) {
        snake->moveSnake();
        snake->wallCollision();
        snake->OST();
        if (snake->getCollision())
            snake->displayScore();
    }
    delete  snake;
    return 0;
}