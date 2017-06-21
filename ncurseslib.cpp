//
// Created by julekgwa on 2017/06/20.
//

#include "ncurseslib.hpp"

WINDOW *init() {
    initscr();
    int height, width, starty, startx;
    getmaxyx(stdscr, height, width);
    curs_set(0);
    starty = (height - (height - 2)) / 2; /* Calculating for a center placement */
    startx = (width - (width - 2)) / 2;
    height -= 2;
    width -= 2;
    halfdelay(1);
    WINDOW *window = newwin(height, width, starty, startx);
    refresh();
    box(window, 0, 0);
    wborder(window, '|', '|', '-', '-', '+', '+', '+', '+');
    wrefresh(window);
    return window;
}

List::List() : _length(0), _head(NULL), _tail(NULL) {}

List::~List() {
    // delete all the nodes
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

void List::printSnakePieces(Food *food, List snakes) {
    char character = snakes.getPiece(1).character;
    int counter = 0;
    Piece tail = snakes.getOldTail();
    char brand[4] = {'C', 'T', 'W', '\0'};
    mvaddch(food->yLoc, food->xLoc, food->character);
    mvaddch(tail.yLoc, tail.xLoc, ' ');
    for (int i = 1; i <= snakes.length(); ++i) {
        Piece snake = snakes.getPiece(i);
        if (i > 1)
            character = '#';
        if (snakes.length() - i >= 0 && snakes.length() - i <= 3 && counter < 3) {
            character = brand[counter++];
        }
        mvaddch(snake.yLoc, snake.xLoc, character);
        refresh();
    }
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