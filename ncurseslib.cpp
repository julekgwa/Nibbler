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