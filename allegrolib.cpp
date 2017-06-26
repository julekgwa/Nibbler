//
// Created by julekgwa on 2017/06/26.
//

#include "allegrolib.hpp"

List::List() {

}

List::List(int width, int height) {
    _fps = 5;
    _direction = RIGHT;
    _redraw = true;
    al_init(); //TODO add error handling
    _display = al_create_display(width, height); //TODO error handling
    al_init_primitives_addon();
    al_install_keyboard();
    al_init_image_addon();
    _bitmap = al_load_bitmap("grass.bmp"); //TODO error handling
    _event_queue = al_create_event_queue();
    _timer = al_create_timer(1.0 / _fps);

    al_register_event_source(_event_queue, al_get_keyboard_event_source());
    al_register_event_source(_event_queue, al_get_display_event_source(_display));
    al_register_event_source(_event_queue, al_get_timer_event_source(_timer));

    al_start_timer(_timer);
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

int List::length() {
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

void List::addHead(int x, int y, char c) {
    Piece *temp = new Piece;
    _length++;
    temp->yLoc = y;
    temp->xLoc = x;
    temp->character = c;
    temp->next = _head;
    _head = temp;
}

bool List::checkPos() {
    Piece *tmp = _head->next;
    while (tmp) {
        if (tmp->xLoc == _head->xLoc && tmp->yLoc == _head->yLoc)
            return true;
        tmp = tmp->next;
    }
    return false;
}

Piece List::getOldTail() {
    return _oldTail;
}

void List::printSnakePieces(Food *food) {
    Piece snake = getPiece(1);
    int x = snake.xLoc, y = snake.yLoc;
    if (_direction == UP) {
        y -= 32;
    } else if (_direction == DOWN) {
        y += 32;
    } else if (_direction == LEFT) {
        x -= 32;
    } else {
        x += 32;
    }

    addHead(x, y, 'c');
    removeTail();
    for (int i = 1; i < length(); ++i) {
        snake = getPiece(i);
        al_draw_bitmap(_bitmap, snake.xLoc, snake.yLoc, 0);
    }
}

void List::displayScore(int score, int maxWidth, int maxHeight) {
    //TODO Implement get score
}

int List::getWidth() {
    return _winWidth;
}

int List::getHeight() {
    return _winHeight;
}

void List::OST(int score) {
    //TODO Implement score
}

int List::getMove() {
    al_wait_for_event(_event_queue, &_event);
    if (_event.type == ALLEGRO_EVENT_TIMER) {
        _redraw = true;
    } else if (_event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        _direction = 'q';
    } else if (_event.type == ALLEGRO_EVENT_KEY_UP) {
        switch (_event.keyboard.keycode) {
            case ALLEGRO_KEY_UP:
                _direction = UP;
                break;

            case ALLEGRO_KEY_DOWN:
                _direction = DOWN;
                break;

            case ALLEGRO_KEY_LEFT:
                _direction = LEFT;
                break;

            case ALLEGRO_KEY_RIGHT:
                _direction = RIGHT;
                break;
            case ALLEGRO_KEY_Q:
                _direction = 'q';
                break;
        }
    }
    if (_redraw && al_is_event_queue_empty(_event_queue)) {
        _redraw = false;

        al_clear_to_color(al_map_rgb(0, 0, 0));

        printSnakePieces(_food);

        al_flip_display();
    }
    return _direction;
}

int List::getMinX() {
    return _minX;
}

int List::getMinY() {
    return _minY;
}

List::~List() {
    al_destroy_event_queue(_event_queue);
    al_destroy_timer(_timer);
    al_destroy_display(_display);
}

List *createList(int x, int y) {
    return new List(x, y);
}

void deleteList(List *list) {
    delete list;
}
