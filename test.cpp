//
// Created by julekgwa on 2017/06/19.
//

#include <iostream>
#include <ncurses.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
typedef struct node {
    int data;
    int xLoc, yLoc;
    char c;
    struct node *next;
} node;

class List {
private:
    node *head, *tail;
    int maxX;
    int maxY;
    int length;
public:
    List();

    void createnode(int value, int, int, char);

    void display(WINDOW *);

    void setMax(int x, int y);

    void delete_last();

    int getLength();

    void moveSnake(WINDOW *win);

    node getSnake(int pos);

    void insert_start(int, int, int, char);

    int getMove(WINDOW *win);
};

List::List() {
    this->head = NULL;
    this->tail = NULL;
    length = 0;
}

int List::getMove(WINDOW *win) {
    int key = wgetch(win);
//    switch (key) {
//        case KEY_UP:
//            this->moveUp();
//            break;
//        case KEY_DOWN:
//            this->moveDown();
//            break;
//        case KEY_LEFT:
//            this->moveLeft();
//            break;
//        case KEY_RIGHT:
//            this->moveRight();
//            break;
//        default:
//            break;
//    }
    return key;
}

node List::getSnake(int pos) {
    node *tmp = new node;
    tmp = head;
    int count = 1;
    while (count != pos && tmp != NULL) {
        count++;
        tmp = tmp->next;
    }
    return *tmp;
}

void List::moveSnake(WINDOW *win) {
    node k = getSnake(1);
    int x = k.xLoc, y = k.yLoc;
    char c = k.c;
    int move = wgetch(win);
    if (move == KEY_UP) {
        y--;
    } else if (move == KEY_DOWN) {
        y++;
    } else if(move == KEY_LEFT)  {
        x--;
    } else {
        x++;
    }

    insert_start(12, x, y, c);
    if (length > 1)
        delete_last();
    wclear(win);
    for (int i = 1; i <= length; ++i) {
        k = getSnake(i);
        mvaddch(k.yLoc, k.xLoc, k.c);
    }
    wrefresh(win);
}

void List::insert_start(int value, int x, int y, char c) {
    node *temp = new node;
    length++;
    temp->data = value;
    temp->yLoc = y;
    temp->xLoc = x;
    temp->c = c;
    temp->next = head;
    head = temp;
}

int List::getLength() {
    return length;
}

void List::setMax(int x, int y) {
    this->maxX = x;
    this->maxY = y;
}

void List::createnode(int value, int xLoc, int yLoc, char c) {
    length++;
    node *temp = new node;
    temp->data = value;
    temp->xLoc = xLoc;
    temp->c = c;
    temp->yLoc = yLoc;
    temp->next = NULL;
    if (head == NULL) {
        head = temp;
        tail = temp;
        temp = NULL;
    } else {
        tail->next = temp;
        tail = temp;
    }
}

void List::delete_last() {
    node *current = new node;
    node *previous = new node;
    current = head;
    while (current->next != NULL) {
        previous = current;
        current = current->next;
    }
    tail = previous;
    length--;
    previous->next = NULL;
    delete current;
}

void List::display(WINDOW *win) {
    node *tmp = new node;
    tmp = head;
    while (getch() != 'x') {
//        cout << tmp->data << "\t";
//        if (tmp->data == 5) {
//            createnode(0);
//        }
        wclear(win);
        wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
        while (tmp) {
            if (tmp->next) {
                tmp->next->yLoc = tmp->yLoc;
                tmp->next->xLoc = tmp->xLoc - 1;
            }

            mvwaddch(win, tmp->yLoc, tmp->xLoc, tmp->c);
            wrefresh(win);
            tmp = tmp->next;
        }

        if ((head->xLoc >= this->maxX || head->yLoc >= this->maxY) || (head->yLoc == 0 || head->xLoc == 0)) {
            mvwprintw(win, 10, 10, "it works cause Khutz did it...", head->yLoc, maxY, head->xLoc, maxX);
            wrefresh(win);
            usleep(1e+9 / 100);
            break;
        }
        if (tmp == NULL) {
            tmp = head;
            tmp->xLoc += 4;
        }
        //usleep()
    }
    endwin();
}


int main() {
    List obj;
//    obj.createnode(6);
//    obj.createnode(0);
//    obj.createnode(0);
//    obj.createnode(0);
//    obj.createnode(0);
//    obj.createnode(0);
//    obj.display();

    initscr();
    int height, width, starty, startx;
    getmaxyx(stdscr, height, width);
    curs_set(0);
    starty = (height - (height - 2)) / 2;    /* Calculating for a center placement */
    startx = (width - (width - 2)) / 2;
    height -= 2;
    width -= 2;
    halfdelay(3);
    WINDOW *win = newwin(height, width, starty, startx);
    refresh();
    box(win, 0, 0);
    wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
    wrefresh(win);
    keypad(win, true);
    obj.createnode(12, width / 2, height / 2, 'C');
    obj.createnode(0, width / 2 - 1, height / 2, '@');
    obj.createnode(0, width / 2 - 2, height / 2, '@');
    obj.createnode(0, width / 2 - 3, height / 2, '@');
//    obj.createnode(0, 0, 0, 'a');
//    obj.createnode(0, 0, 0, 'b');
//    obj.setMax(width, height);
    int move = 0;
    while (getch() != 'x') {
        obj.moveSnake(win);
        wrefresh(win);
    }
    endwin();
    return 0;
}