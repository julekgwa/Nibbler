//
// Created by julekgwa on 2017/06/20.
//

#include "Snake.hpp"

int main(int ac, char *argv[]) {

    if (ac < 3)
    {
        std::cout << "3 arguments required" << std::endl;
        exit(EXIT_FAILURE);
    }

    int x, y;
    try {
        x = std::stoi(argv[1]);
        y = std::stoi(argv[2]);

        Snake *snake = new Snake(x,y);
        while (snake->getMove() != 'q' && !snake->getCollision()) {
            snake->moveSnake();
            snake->wallCollision();
            snake->OST();
            if (snake->getCollision())
                snake->displayScore();
        }
        delete  snake;

    }
    catch (std::invalid_argument &e)
    {
        std::cout << "Values passed must be integers" << std::endl;
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}