#include "Node.h"

Node::Node(Tile* data, Node* next, Node* prev) {
    this->data = data;
    this->next = next;
    this->prev = prev;
}

Node::~Node() {
    delete data;
}


Tile* Node::getData() {
    return data;
}

Node* Node::getNext(){
    return next;
}

Node* Node::getPrevious(){
    return prev;
}


void Node::setData(Tile* data) {
    this->data = data;
}

void Node::setNext(Node* next){
    this->next = next;
}

void Node::setPrevious(Node* prev){
    this->prev = prev;
}

