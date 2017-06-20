//
// Created by julekgwa on 2017/06/20.
//

#include "List.hpp"

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

void List::insertHead(int x, int y, char c) {
    Piece *temp = new Piece;
    _length++;
    temp->yLoc = y;
    temp->xLoc = x;
    temp->character = c;
    temp->next = _head;
    _head = temp;
}

void List::removeTail() {
    Piece *current = new Piece;
    Piece *previous = new Piece;
    current = _head;
    while (current->next != NULL) {
        previous = current;
        current = current->next;
    }
    _tail = previous;
    _length--;
    previous->next = NULL;
    delete current;
}