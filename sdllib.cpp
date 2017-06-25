//
// Created by Junius LEKGWARA on 2017/06/24.
//

#include "sdllib.hpp"

List::List() {}

List::List(int x, int y) throw (myYtooBig, myYtooSmall,myXtooBig,myXtooSmall) : _length(0), _head(NULL), _tail(NULL) {

    if (x > MAXWIDTH)
    {
        throw myXtooBig();
    }
    else if (x < MINWIDTH)
    {
        throw myXtooSmall();
    }
    else if (y < MINHEIGHT)
    {
        throw myYtooSmall();
    }
    else if (y > MAXHEIGHT)
    {
        throw myYtooBig();
    }

    SDL_Init(SDL_INIT_EVERYTHING);
    //For loading PNG images
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();
    _background_surface = NULL;
    _background_texture = NULL;
    _width = x;
    _height = y;
    _sdl_window = SDL_CreateWindow("Nibbler retro", SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED, _width, _height, SDL_WINDOW_SHOWN);
    _renderer = SDL_CreateRenderer(_sdl_window, -1, SDL_RENDERER_PRESENTVSYNC);
    _background_surface = SDL_LoadBMP("grass.bmp");
    _head_surface = SDL_LoadBMP("head.bmp");
    _food_background_surface = SDL_LoadBMP("apple.bmp");
    _background_texture = SDL_CreateTextureFromSurface(_renderer, _background_surface);
    _food_background_texture = SDL_CreateTextureFromSurface(_renderer, _food_background_surface);
    _head_texture = SDL_CreateTextureFromSurface(_renderer, _head_surface);
    _quit = false;
    setTexture(_background_texture);
    _food = new Food;
    _minX = 0;
    _eaten = false;
    _minY = 0;
    _score = 0;
    _foodY = 34;
    _foodX = 78;
    collision = SDL_HasIntersection(&_food_rect, &_rect);
    _direction = RIGHT;
}

List    &List::operator=(List &) {
    return *this;
}

List::List(List &) {}

int List::getMinX() {
    return _minX;
}

int List::getMinY() {
    return _minY;
}

const char* List::myYtooBig::what() const throw()
{
    return "The height supplied is bigger than is possible in this window for SDL lib.";
}

List::myYtooBig::myYtooBig(void) {}

List::myYtooBig::myYtooBig(myYtooBig const &obj) {
    *this = obj;
}

List::myYtooBig& List::myYtooBig::operator=(myYtooBig const &) {
    return *this;
}
//
List::myYtooBig::~myYtooBig() throw() {}

const char* List::myYtooSmall::what() const throw()
{
    return "The height supplied is too small for possible gameplay in the SDL lib.";
}

List::myYtooSmall::myYtooSmall(void) {}

List::myYtooSmall::myYtooSmall(myYtooSmall const &obj) {
    *this = obj;
}

List::myYtooSmall& List::myYtooSmall::operator=(myYtooSmall const &) {
    return *this;
}

List::myYtooSmall::~myYtooSmall() throw() {}

const char* List::myXtooBig::what() const throw()
{
    return "The width supplied is bigger than is possible in this window for SDL lib.";
}

List::myXtooBig::myXtooBig(void) {}

List::myXtooBig::myXtooBig(myXtooBig const &obj) {
    *this = obj;
}

List::myXtooBig& List::myXtooBig::operator=(myXtooBig const &) {
    return *this;
}

List::myXtooBig::~myXtooBig() throw() {}

const char* List::myXtooSmall::what() const throw()
{
    return "The width supplied is too small for possible gameplay in the SDL lib.";
}

List::myXtooSmall::myXtooSmall(void) {}

List::myXtooSmall::myXtooSmall(myXtooSmall const &obj) {
    *this = obj;
}

List::myXtooSmall& List::myXtooSmall::operator=(myXtooSmall const &) {
    return *this;
}

List::myXtooSmall::~myXtooSmall() throw() {}

List::~List() {
    //Deleting the texture
    SDL_DestroyTexture(_background_texture);
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_sdl_window);
    //For quitting IMG systems
    IMG_Quit();
    SDL_Quit();
}

Piece List::getPiece(int pos) {
    Piece *tmp = new Piece;
    tmp = _head;
    int count = 1;
    while (count != pos && tmp != NULL) {
        count++;
        tmp = tmp->next;
    }
    return *tmp;
}

Food *List::generateFood() {
    srand(time(NULL)); // Seed the time
    int y = rand() % ((int) (_height - 10 + 1) + 2);
    int x = rand() % ((int) (_width - 10 + 1) + 2);
    if (y >= _height)
        y = _width - 2;
    if (y <= 1) {
        y = 3;
    }
    if (x >= _height)
        x = _width - 2;
    if (x <= 1)
        x = 3;
    _food->xLoc = x;
    _food->yLoc = y;
    _foodX = rangeRandom(5, _width - 15);
    _foodY = rangeRandom(5, _height - 15);
    _food->character = 'x';
    return _food;
}

int List::rangeRandom(int min, int max) {
    int n = max - min + 1;
    int remainder = RAND_MAX % n;
    int x;
    do {
        x = rand();
    } while (x >= RAND_MAX - remainder);
    return min + x % n;
}

void List::addHead(int x, int y, char c) {
    Piece *temp = new Piece;
    _length++;
    temp->yLoc = y;
    temp->xLoc = x;
    temp->character = c;
    temp->next = _head;
    _head = temp;
}

bool List::checkPos() {
    Piece *tmp = _head->next;
    while (tmp) {
        if ((tmp->xLoc == _head->xLoc && tmp->yLoc == _head->yLoc))
            return true;
        tmp = tmp->next;
    }
    return false;
}

int List::getMove() {
//    while (!_quit) {
    while (SDL_PollEvent(&_event) > 0) {
        if (_event.type == SDL_QUIT) {
            _quit = true;
            _direction = 'q';
        }
    }

    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderClear(_renderer);
    _keystate = SDL_GetKeyboardState(NULL);

    if (_keystate[SDL_SCANCODE_LEFT]) {
        if (_direction != RIGHT)
            _direction = LEFT;
    } else if (_keystate[SDL_SCANCODE_UP]) {
        if (_direction != DOWN)
            _direction = UP;
    } else if (_keystate[SDL_SCANCODE_DOWN]) {
        if (_direction != UP)
            _direction = DOWN;
    } else if (_keystate[SDL_SCANCODE_RIGHT]) {
        if (_direction != LEFT)
            _direction = RIGHT;
    } else if (_keystate[SDL_SCANCODE_Q]) {
        _quit = true;
        _direction = 'q';
    } else if (_keystate[SDL_SCANCODE_1]) {
        _direction = 'w';
    }
    printSnakePieces(_food);
    OST(_score);
//    TTF_Font *font = TTF_OpenFont("gomarice.ttf", 20);
//    std::string score_text = "score: " + std::to_string(_score);
//    SDL_Color textColor = { 255, 255, 255, 0 };
//    SDL_Surface* textSurface = TTF_RenderText_Solid(font, score_text.c_str(), textColor);
//    SDL_Texture* text = SDL_CreateTextureFromSurface(_renderer, textSurface);
//    int text_width = textSurface->w;
//    int text_height = textSurface->h;
//    SDL_FreeSurface(textSurface);
//    SDL_Rect renderQuad = { 20, _height - 30, text_width, text_height };
//    SDL_RenderCopy(_renderer, text, NULL, &renderQuad);
//    SDL_RenderFillRect(_renderer, &_rect);
    SDL_RenderPresent(_renderer);
    SDL_Delay(100);
//    }
    return _direction;
}

SDL_bool List::test() {
    SDL_Rect a;
    SDL_Rect *c;
    Piece piece = getPiece(1);
    a.x = piece.xLoc;
    a.y = piece.yLoc;
    a.h = 8;
    a.w = 8;
    return SDL_IntersectRect(&_food_rect, &a, c);
}

void List::OST(int score) {
    TTF_Font *font = TTF_OpenFont("gomarice.ttf", 20);
    std::string score_text = "score: " + std::to_string(score);
    SDL_Color textColor = { 255, 255, 255, 0 };
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, score_text.c_str(), textColor);
    SDL_Texture* text = SDL_CreateTextureFromSurface(_renderer, textSurface);
    int text_width = textSurface->w;
    int text_height = textSurface->h;
    SDL_FreeSurface(textSurface);
    SDL_Rect renderQuad = { 20, _height - 30, text_width, text_height };
    SDL_RenderCopy(_renderer, text, NULL, &renderQuad);
}

int List::getHeight() {
    return _height;
}

int List::getWidth() {
    return _width;
}

Piece List::getOldTail() {
    return _oldTail;
}

void List::removeTail() {
    Piece *current;
    Piece *previous;
    current = _head;
    while (current->next != NULL) {
        previous = current;
        current = current->next;
    }
    _tail = previous;
    _length--;
    previous->next = NULL;
    _oldTail = *current;
}

int List::length() {
    return _length;
}

//void List::draw(Piece piece) {
////    SDL_Rect rect;
//    _rect.x = piece.xLoc;
//    _rect.y = piece.yLoc;
//    _rect.w = 16;
//    _rect.h = 16;
//    SDL_RenderCopy(_renderer, _background_texture, NULL, &_rect);
////    SDL_RenderPresent(_renderer);
//}

void List::draw(Piece piece, SDL_Texture *texture) {
    _rect.x = piece.xLoc;
    _rect.y = piece.yLoc;
    _rect.w = 16;
    _rect.h = 16;
    SDL_RenderCopy(_renderer, texture, NULL, &_rect);
}

void List::drawFruit() {
    SDL_Rect rect;
    rect.x = _foodX;
    rect.y = _foodY;
    rect.w = 20;
    rect.h = 20;
    _food_rect = rect;
    SDL_RenderCopy(_renderer, _food_background_texture, NULL, &_food_rect);
//    SDL_RenderPresent(_renderer);
}

void List::printSnakePieces(Food *food) {
    SDL_Texture *texture = _head_texture;
    Piece snake = getPiece(1);
    int x = snake.xLoc, y = snake.yLoc;
    if (_direction == UP) {
        y = y - 16;
    } else if (_direction == DOWN) {
        y = y + 16;
    } else if (_direction == LEFT) {
        x = x - 16;
    } else {
        x = x + 16;
    }
    addHead(x, y, snake.character);
    drawFruit();
    if (test()) {
        SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 255);
        _food = generateFood();
        _score++;
    } else
        removeTail();
    for (int i = 1; i <= _length; ++i) {
        if (i > 1)
            texture = _background_texture;
        draw(getPiece(i), texture);
    }
}

void List::displayScore(int _score, int _maxWidth, int _maxHeight) {

}

void List::setTexture(SDL_Texture *texture) {
    _background_texture = texture;
}

SDL_Texture *List::getTexture() {
    return _background_texture;
}

List *createList(int x, int y) {
    return new List(x, y);
}

void deleteList(List *list) {
    delete list;
}