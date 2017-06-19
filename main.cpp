//
// Created by julekgwa on 2017/06/19.
//

#include <iostream>
#include <ncurses.h>

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
public:
    List();

    void createnode(int value, int, int, char);

    void display(WINDOW *);
};

List::List() {
    this->head = NULL;
    this->tail = NULL;
}

void List::createnode(int value, int xLoc, int yLoc, char c) {
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

void List::display(WINDOW *win) {
    node *tmp = new node;
    tmp = head;
    while (getch() != 'x') {
//        cout << tmp->data << "\t";
//        if (tmp->data == 5) {
//            createnode(0);
//        }
        if (tmp->next) {
            tmp->next->yLoc = tmp->yLoc;
            tmp->next->xLoc = tmp->xLoc - 1;
        }

        mvwaddch(win, tmp->yLoc, tmp->xLoc, tmp->c);
        wrefresh(win);
        tmp = tmp->next;
        if (tmp == NULL) {
            tmp = head;
            tmp->xLoc += 4;
            mvwaddch(win, tmp->yLoc, tmp->xLoc - 1, ' ');
            mvwaddch(win, tmp->yLoc, tmp->xLoc - 2, ' ');
            mvwaddch(win, tmp->yLoc, tmp->xLoc - 3, ' ');
            mvwaddch(win, tmp->yLoc, tmp->xLoc - 4, ' ');
            mvwaddch(win, tmp->yLoc, tmp->xLoc - 5, ' ');
            mvwaddch(win, tmp->yLoc, tmp->xLoc - 6, ' ');
            mvwaddch(win, tmp->yLoc, tmp->xLoc - 7, ' ');
        }
    }
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
    halfdelay(1);
    WINDOW *win = newwin(height, width, starty, startx);
    refresh();
    box(win, 0, 0);
    wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
    wrefresh(win);
    obj.createnode(12, width / 2,  height / 2, '@');
    obj.createnode(0,0,0,'@');
    obj.createnode(0,0,0,'@');
    obj.createnode(0,0,0,'@');
    obj.display(win);
    int g = getch();
    return 0;
}