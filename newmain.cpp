#include <dlfcn.h>
#include "Snake.hpp"
#include "IList.hpp"


void    dlerror_wrapper(void)
{
    std::cerr << "Error: " << dlerror() << std::endl;
    exit(EXIT_FAILURE);
}

int main() {
//    Snake *snake = new Snake();
//    while (snake->getMove() != 'q' && !snake->getCollision()) {
//        snake->moveSnake();
//        snake->wallCollision();
//        snake->OST();
//        if (snake->getCollision())
//            snake->displayScore();
//    }
//    delete  snake;

    void    *dl_handle;

    dl_handle = dlopen("ncurseslib.so", RTLD_LAZY | RTLD_LOCAL);

    if (!dl_handle)
        dlerror_wrapper();

    void    (*test)(void);

    test = (void(*)(void)) dlsym(dl_handle,"test");

    if (!test)
        dlerror_wrapper();

    test();

    IList   *(*createList)(void);

    createList = (IList *(*)(void)) dlsym(dl_handle,"createList");

    if (!createList)
        dlerror_wrapper();

    IList   *list = createList();

    std::cout << list->getHeight() << std::endl;

    dlclose(dl_handle);

    return 0;
}