//
// Created by julekgwa on 2017/06/19.
//

#include <iostream>
#include <ncurses.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
typedef struct node
{
    int data;
    int xLoc, yLoc;
    char c;
    struct node *next;
} node;

class List
{
  private:
    node *head, *tail;
    int maxX;
    int maxY;

  public:
    List();

    void createnode(int value, int, int, char);

    void display(WINDOW *);
    bool collide(WINDOW *);
    void setMax(int x, int y);
};

List::List()
{
    this->head = NULL;
    this->tail = NULL;
}

void List::setMax(int x, int y)
{
    this->maxX = x;
    this->maxY = y;
}

void List::createnode(int value, int xLoc, int yLoc, char c)
{
    node *temp = new node;
    temp->data = value;
    temp->xLoc = xLoc;
    temp->c = c;
    temp->yLoc = yLoc;
    temp->next = NULL;
    if (head == NULL)
    {
        head = temp;
        tail = temp;
        temp = NULL;
    }
    else
    {
        tail->next = temp;
        tail = temp;
    }
}
bool List::collide(WINDOW *win)
{
    node *tmp = new node;
    tmp = head;
    tmp = tmp->next;
    //check to see if the snake has collided with the wall.
    if ((tmp->xLoc >= this->maxX || tmp->yLoc >= this->maxY) || (tmp->yLoc <= 0 || tmp->xLoc <= 0))
        {
            mvwprintw(win, 10, 10, "Hit Wall", head->yLoc, maxY, head->xLoc, maxX);
            wrefresh(win);
            //slow down the game to allow for viewing of the message.
            usleep(1e+9 / 100);
            return (true);
        }
    //check if the head of the snake is at the same position as on of its body parts;
    while (tmp)
    {
        if ((tmp->xLoc  == head->xLoc && tmp->yLoc == head->yLoc))
        {
            mvwprintw(win, 10, 10, "eat self", head->yLoc, maxY, head->xLoc, maxX);
            wrefresh(win);
            //slow down the game to allow for viewing of the message.
            usleep(1e+9 / 100);
            return (true);
        }
        tmp = tmp->next;
    }
    return (false);
}
void List::display(WINDOW *win)
{
    node *tmp = new node;
    tmp = head;
    while (getch() != 'x')
    {
        //        cout << tmp->data << "\t";
        //        if (tmp->data == 5) {
        //            createnode(0);
        //        }
        wclear(win);
        wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
        while (tmp)
        {
            if (tmp->next)
            {
                tmp->next->yLoc = tmp->yLoc;
                tmp->next->xLoc = tmp->xLoc - 1;
            }

            mvwaddch(win, tmp->yLoc, tmp->xLoc, tmp->c);
            wrefresh(win);
            tmp = tmp->next;
        }
        //check for collision
        if (collide(win)){
            break;
        }
        if (tmp == NULL)
        {
            tmp = head;
            tmp->xLoc += 1;
        }
    }
    endwin();
}

int main()
{
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
    starty = (height - (height - 2)) / 2; /* Calculating for a center placement */
    startx = (width - (width - 2)) / 2;
    height -= 2;
    width -= 2;
    halfdelay(1);
    WINDOW *win = newwin(height, width, starty, startx);
    refresh();
    box(win, 0, 0);
    wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
    wrefresh(win);
    obj.createnode(12, width / 2, height / 2, 'C');
    obj.createnode(0, 0, 0, '@');
    obj.createnode(0, 0, 0, '@');
    obj.createnode(0, 0, 0, '@');
    obj.setMax(width, height);
    obj.display(win);
    endwin();
    return 0;
}