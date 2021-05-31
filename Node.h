#ifndef NODE_H
#define NODE_H

#include "Tile.h"

class Node {
    public:
    /**
     * Node constructor
     * input:
     * data as Tile*
     * next as Node*
     * prev as Node*
     */
    Node(Tile* data, Node* next, Node* prev);
    ~Node();
    Tile* getData();
    Node* getNext();
    Node* getPrevious();
    void setData(Tile* tile);
    void setNext(Node* next);
    void setPrevious(Node* prev);

    // PLEASE CLARIFY
    // shouldn't these variables be declared as private ?? 


    private:
    Tile* data;
    Node* next;
    Node* prev;



};

#endif // NODE_H