//
// Created by julekgwa on 2017/06/19.
//

#include <iostream>

using namespace std;
typedef struct node {
    int data;
    struct node *next;
} node;

class List {
private:
    node *head, *tail;
public:
    List();

    void createnode(int value);

    void display();
};

List::List() {
    this->head = NULL;
    this->tail = NULL;
}

void List::createnode(int value) {
    node *temp = new node;
    temp->data = value;
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

void List::display() {
    node *tmp = new node;
    tmp = head;
    while (tmp != NULL) {
        cout << tmp->data << "\t";
        if (tmp->data == 5) {
            createnode(0);
        }
        if (tmp->next)
            tmp->next->data = tmp->data - 1;
        tmp = tmp->next;
    }
}


int main() {
    List obj;
    obj.createnode(6);
    obj.createnode(0);
    obj.createnode(0);
    obj.createnode(0);
    obj.createnode(0);
    obj.createnode(0);
    obj.display();
    return 0;
}