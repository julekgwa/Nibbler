//
// Created by julekgwa on 2017/06/20.
//

#include "ncursescolorlib.hpp"

List::List() {}

List::List(int x, int y) throw (myYtooBig, myYtooSmall,myXtooBig,myXtooSmall) : _length(0), _head(NULL), _tail(NULL) {
    int starty, startx;
    initscr();
    getmaxyx(stdscr, height, width);
    if (x > width)
    {
        endwin();
        throw myXtooBig();
    }
    else if (x < 100)
    {
        endwin();
        throw myXtooSmall();
    }
    else if (y < 10)
    {
        endwin();
        throw myYtooSmall();
    }
    else if (y > height)
    {
        endwin();
        throw myYtooBig();
    }
    if (has_colors() == FALSE)
    {
        endwin();
        printf("Your terminal does not support color\n");
        exit(1);
    }
    start_color();
    init_pair(1, COLOR_RED, COLOR_RED);
    init_pair(2, COLOR_GREEN, COLOR_YELLOW);
    init_pair(3, COLOR_BLACK, COLOR_RED);
    init_pair(4, COLOR_BLUE, COLOR_BLUE);
    init_pair(5, COLOR_MAGENTA, COLOR_YELLOW);
    height = y;
    width = x;
    _minHeight = 1;
    _minWidth = 1;
    curs_set(0);
    starty = (height - (height - 2)) / 2; /* Calculating for a center placement */
    startx = (width - (width - 2)) / 2;
    height -= 2;
    width -= 2;
    halfdelay(1);
    _window = newwin(height, width, starty, startx);
    bkgd(COLOR_PAIR(3));
    wbkgd(_window, ' ' + COLOR_PAIR(1));
    refresh();
    wattron(_window, COLOR_PAIR(5) + A_BOLD);
    box(_window, 0, 0);
    wborder(_window, '|', '|', '-', '-', '+', '+', '+', '+');
    wattroff(_window, COLOR_PAIR(5) + A_BOLD);
    wrefresh(_window);
    keypad(_window, true);
}

int     List::getMinWidth(void)
{
    return this->_minWidth;
}

int     List::getMinHeight(void)
{
    return this->_minHeight;
}

List    &List::operator=(List &) {
    return *this;
}

List::List(List &) {}

const char* List::myYtooBig::what() const throw()
{
    return "The height supplied is bigger than is possible in this window for ncurses lib.";
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
    return "The height supplied is too small for possible gameplay in the ncurses lib.";
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
    return "The width supplied is bigger than is possible in this window for ncurses lib.";
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
    return "The width supplied is too small for possible gameplay in the ncurses lib.";
}

List::myXtooSmall::myXtooSmall(void) {}

List::myXtooSmall::myXtooSmall(myXtooSmall const &obj) {
    *this = obj;
}

List::myXtooSmall& List::myXtooSmall::operator=(myXtooSmall const &) {
    return *this;
}

List::myXtooSmall::~myXtooSmall() throw() {}

void    List::OST(int _score)
{
    mvprintw(height + 1, 2, "score: %d :: %d :: %d", _score,width,height);
    refresh();
}

List::~List() {
    endwin();// delete all the nodes
}

int List::getMove() {
    int key = wgetch(_window);
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
        case 'q':
            _direction = 'q';
    }
    return _direction;
}

int     List::getWidth()
{
    return this->width;
}

int     List::getHeight()
{
    return this->height;
}

int List::length(){
    return _length;
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

bool List::checkPos()
{
    Piece *tmp = _head->next;
    while (tmp)
    {
        if (tmp->xLoc == _head->xLoc && tmp->yLoc == _head->yLoc)
            return true;
        tmp = tmp->next;
    }
    return false;
}

void List::addHead(int x, int y, char c){
    Piece *temp = new Piece;
    _length++;
    temp->yLoc = y;
    temp->xLoc = x;
    temp->character = c;
    temp->next = _head;
    _head = temp;
}

void List::printSnakePieces(Food *food) {
    char character = this->getPiece(1).character;
    int counter = 0;
    Piece tail = this->getOldTail();
    char brand[4] = {'C', 'T', 'W', '\0'};
    mvaddch(food->yLoc, food->xLoc, food->character);
    mvaddch(tail.yLoc, tail.xLoc, ' ');
    for (int i = 1; i <= this->length(); ++i) {
        Piece snake = this->getPiece(i);
        if (i > 1)
            character = '#';
        if (this->length() - i >= 0 && this->length() - i <= 3 && counter < 3) {
            character = brand[counter++];
        }
        mvaddch(snake.yLoc, snake.xLoc, character);
        refresh();
    }
}

void List::displayScore(int _score, int _maxWidth, int _maxHeight) {
    std::stringstream score;

    clear();
    mvprintw((_maxHeight / 2), (_maxWidth / 2), "******************************");
    score.str("");
    score << "*Your final Score was:" << std::left << std::setfill('*') << std::setw(8) << _score;
    mvprintw((_maxHeight / 2) + 1, (_maxWidth / 2), score.str().c_str());
    mvprintw((_maxHeight / 2) + 2, (_maxWidth / 2), "******************************");
    refresh();
    usleep(1e+9 / 200);
    return;
}

Piece List::getOldTail()
{
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

List    *createList(int x, int y)
{
    return new List(x,y);
}

void    deleteList(List *list)
{
    delete list;
}

void    test()
{
    std::cout << "I'm killing it" << std::endl;
}