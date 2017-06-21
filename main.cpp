//
// Created by julekgwa on 2017/06/20.
//

#include "Snake.hpp"

int main() {
    WINDOW *window = init();
    Snake *snake = new Snake(window);
    while (snake->getMove() != 'q' && !snake->getCollision()) {
        snake->moveSnake();
        snake->wallCollision();
        snake->OST();
        if (snake->getCollision()) {
            snake->displayScore();
            sleep(3);
        }
    }
    endwin();
    return 0;
}