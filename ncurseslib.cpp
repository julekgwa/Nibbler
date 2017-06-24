//
// Created by julekgwa on 2017/06/20.
//

#include "ncurseslib.hpp"

List::List() : _length(0), _head(NULL), _tail(NULL) {
    initscr();
    int starty, startx;
    getmaxyx(stdscr, height, width);
    curs_set(0);
    starty = (height - (height - 2)) / 2; /* Calculating for a center placement */
    startx = (width - (width - 2)) / 2;
    height -= 2;
    width -= 2;
    halfdelay(1);
    _window = newwin(height, width, starty, startx);
    refresh();
    box(_window, 0, 0);
    wborder(_window, '|', '|', '-', '-', '+', '+', '+', '+');
    wrefresh(_window);
}

WINDOW *List::getWindow()
{
    return _window;
}

void    List::OST(int _score)
{
    mvprintw(height + 1, 2, "score: %d", _score);
    refresh();
}

List::~List() {
    // delete all the nodes
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

List    *createList()
{
    return new List;
}

void    deleteList(List *list)
{
    delete list;
}

void    test()
{
    std::cout << "I'm killing it" << std::endl;
}