//
// Created by julekgwa on 2017/06/20.
//

#include "Listlib.hpp"
List::List() : _length(0), _head(NULL), _tail(NULL)
{
    initscr();
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
    int starty, startx;
    getmaxyx(stdscr, height, width);
    curs_set(0);
    starty = (height - (height - 2)) / 2;
    startx = (width - (width - 2)) / 2;
    height -= 2;
    width -= 2;
    halfdelay(1);
    _window = newwin(height, width, starty, startx);
    bkgd(COLOR_PAIR(5));
    wbkgd(_window, '.' + COLOR_PAIR(5));
    refresh();
    wattron(_window,COLOR_PAIR(2) + A_BOLD);
    box(_window, 0, 0);
    wborder(_window, '|', '|', '-', '-', '+', '+', '+', '+');
    wattroff(_window,COLOR_PAIR(2) + A_BOLD);
    wrefresh(_window);
}

List::List(List &rhs){
    *this = rhs;
}

List::operator=(List &rhs){
    this->_length = rhs.length();
    this->_window = rhs.getWindow();
    this->_height = rhs.getHeight();
    this->_width = rhs.getWidth();
    this->_oldTail = rhs.getOldTail();
    return (*this);
}
WINDOW *List::getWindow()
{
    return _window;
}

void List::OST(int _score)
{
    attron(COLOR_PAIR(2) + A_BOLD);
    mvprintw(height + 1, 2, "score: %d", _score);
    attroff(COLOR_PAIR(2) + A_BOLD);
    refresh();
}

List::~List()
{
    // delete all the nodes
}

int List::length()
{
    return _length;
}

Piece List::getPiece(int pos)
{
    Piece *tmp = new Piece;
    tmp = _head;
    int count = 1;
    while (count != pos && tmp != NULL)
    {
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

void List::addHead(int x, int y, char c)
{
    Piece *temp = new Piece;
    _length++;
    temp->yLoc = y;
    temp->xLoc = x;
    temp->character = c;
    temp->next = _head;
    _head = temp;
}

void List::printSnakePieces(Food *food, List snakes)
{
    char character = snakes.getPiece(1).character;
    Piece tail = snakes.getOldTail();
    attron(COLOR_PAIR(2) + A_BOLD);
    mvaddch(food->yLoc, food->xLoc, food->character);
    attroff(COLOR_PAIR(2) + A_BOLD);
    attron(COLOR_PAIR(5));
    mvaddch(tail.yLoc, tail.xLoc, '.');
    attroff(COLOR_PAIR(5));
    for (int i = 1; i <= snakes.length(); ++i)
    {
        Piece snake = snakes.getPiece(i);
        if (i == 1){
            character = '#';
            attron(COLOR_PAIR(4)  + A_BOLD);
            mvaddch(snake.yLoc, snake.xLoc, character);
            attroff(COLOR_PAIR(4)  + A_BOLD);
        }
        if (i > 1)
        {
            character = '#';
            attron(COLOR_PAIR(1)  + A_BOLD);
            mvaddch(snake.yLoc, snake.xLoc, character);
            attroff(COLOR_PAIR(1) + A_BOLD);
        }
        refresh();
    }
}

void List::displayScore(int _score, int _maxWidth, int _maxHeight)
{
    std::stringstream score;
    clear();
    mvprintw((_maxHeight / 2) - 1, (_maxWidth / 2)  - (5), "GAME OVER!");
    attron(COLOR_PAIR(1));
    mvprintw((_maxHeight / 2), (_maxWidth / 2) - (30 /2), "******************************");
    attroff(COLOR_PAIR(1));
    score.str("");
    score << "*Your final Score was:" << std::left << std::setfill('*') << std::setw(8) << _score;
    mvprintw((_maxHeight / 2) + 1, (_maxWidth / 2)  - (30 /2), score.str().c_str());
    attron(COLOR_PAIR(1));
    mvprintw((_maxHeight / 2) + 2, (_maxWidth / 2) - (30 /2), "******************************");
    attroff(COLOR_PAIR(1));
    refresh();
    usleep(1e+9 / 200);
    return;
}

Piece List::getOldTail()
{
    return _oldTail;
}

void List::removeTail()
{
    Piece *current;
    Piece *previous;
    current = _head;
    while (current->next != NULL)
    {
        previous = current;
        current = current->next;
    }
    _tail = previous;
    _length--;
    previous->next = NULL;
    _oldTail = *current;
}