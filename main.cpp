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
    int oldX, oldY;
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
    bool collide2(WINDOW *, int x, int y);
    void eat(List, int foodx, int foody);
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
//eat method for adding new cell to snake to be expanded for scoring
void List::eat(List obj /* to be passed by reference*/, int foodx, int foody)
{
    if (head->xLoc == foodx || head->yLoc >= foody)
    {
        obj.createnode(0, 0, 0, '@');
    }
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
//revised collision
bool List::collide2(WINDOW *win, int x, int y)
{
    node *tmp = head;
    tmp = tmp->next;
    if ((head->xLoc == this->maxX - 1 || head->yLoc == this->maxY) || (head->xLoc == 0 || head->yLoc == 0))
    {
        mvwprintw(win, 10, 10, "Hit Wall at X::%d-%d Y::%d-%d", head->xLoc, maxX, head->yLoc, maxY);
        //reprint  the entire snake on collision
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
        wrefresh(win);
        //slow down the game to allow for viewing of the message.
        usleep(1e+9 / 100);
        return (true);
    }
    //check if the head of the snake is at the same position as the current body part being rendered;
    if ((head->xLoc == x && head->yLoc == y))
    {
//        mvwprintw(win, 10, 10, "eat self");
//        //reprint  the entire snake on collision
//        while (tmp)
//        {
//            if (tmp->next)
//            {
//                tmp->next->yLoc = tmp->yLoc;
//                tmp->next->xLoc = tmp->xLoc - 1;
//            }
//            mvwaddch(win, tmp->yLoc, tmp->xLoc, tmp->c);
//            wrefresh(win);
//            tmp = tmp->next;
//        }
//        wrefresh(win);
//        //slow down the game to allow for viewing of the message.
//        usleep(1e+9 / 100);
//        return (true);
    }
    return (false);
}
//first collision made....rev 2 is better
bool List::collide(WINDOW *win)
{
    node *tmp = head;
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
    if ((tmp->xLoc == head->xLoc && tmp->yLoc == head->yLoc))
    {
        mvwprintw(win, 10, 10, "eat self", head->yLoc, maxY, head->xLoc, maxX);
        wrefresh(win);
        //slow down the game to allow for viewing of the message.
        usleep(1e+9 / 100);
        return (true);
    }
    return (false);
}
void List::display(WINDOW *win)
{
    node *tmp = head;
    char c = '\0';
    bool up = false;
    bool down = false;
    bool right = true;
    bool left = false;
    while (1)
    {
        wclear(win);
        wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
        while (tmp)
        {
            if (tmp->next)
            {
                if (right)
                {
                    tmp->next->yLoc = tmp->yLoc;
                    tmp->next->xLoc = tmp->xLoc - 1;
                }
                else if (up)
                {
                    tmp->next->xLoc = tmp->xLoc;
                    tmp->next->yLoc = tmp->yLoc + 1;
                }
                else if (down)
                {
                    tmp->next->xLoc = tmp->xLoc;
                    tmp->next->yLoc = tmp->yLoc - 1;
                }
                else if (left)
                {
                    tmp->next->yLoc = tmp->yLoc;
                    tmp->next->xLoc = tmp->xLoc + 1;
                }
            }
//            if (tmp != head)
//            {
//
//            }
            mvwaddch(win, tmp->yLoc, tmp->xLoc, tmp->c);
            wrefresh(win);
            tmp = tmp->next;
        }
        if (collide2(win, head->xLoc, head->yLoc))
        {
            break;
        }
        c = getchar();
        if (c == 'x')
            break ;
        if (c == 'w' && !down)
        {
            up = true;
            left = false;
            right = false;
            down = false;
        }
        else if (c == 'd' && !left)
        {
            up = false;
            left = false;
            right = true;
            down = false;
        }
        else if (c == 'a' && !right)
        {
            up = false;
            left = true;
            right = false;
            down = false;
        }
        else if (c == 's' && !up)
        {
            up = false;
            left = false;
            right = false;
            down = true;
        }
        if (tmp == NULL)
        {
            tmp = head;
            if (right)
            {
                tmp->oldX = tmp->xLoc;
                tmp->xLoc += 1;
            }
            else if (left)
            {
                tmp->oldX = tmp->xLoc;
                tmp->xLoc -= 1;
            }
            else if (up)
            {
                if (tmp->xLoc != head->xLoc)
                {
                    tmp->xLoc += 1;
                }
                else
                {
                    tmp->yLoc -= 1;
                }
            }
            else if (down)
            {
                if (tmp->xLoc != head->xLoc)
                {
                    tmp->xLoc += 1;
                }
                else
                {
                    tmp->yLoc += 1;
                }
            }
        }
    }
    endwin();
}

int main()
{
    List obj;

    initscr();
    noecho();
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
    obj.createnode(12, width / 2, height / 2, '>');
    obj.createnode(0, 0, 0, '#');
    obj.createnode(0, 0, 0, '#');
    obj.createnode(0, 0, 0, '#');
    obj.setMax(width, height);
    obj.display(win);
    endwin();
    return 0;
}