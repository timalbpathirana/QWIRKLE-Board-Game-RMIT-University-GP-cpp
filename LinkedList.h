#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Tile.h"
#include "Node.h"
#include <iostream>

class LinkedList {
    public:
        /**
         * LinkedList constructor
         * no input
         */
        LinkedList();
        ~LinkedList();

        /**
         * output: size of linked list
         */
        int getSize();

        /**
         * input: index as int
         * output: the Tile* at index, head is 0
         */
        Tile* getIndex(int index);

        /**
         * add a new Node at the beginning of the linked list (index 0)
         * input: data as Tile*
         * output: none
         */
        void addFront(Tile* data);
        /**
         * add a new Node at the end of the linked list (index size)
         * input: data as Tile*
         * output: none
         */
        void addBack(Tile* data);

            // /**
            //  * delete the pointer to the Node at the beginning of the linked list (head node)
            //  * the Tile object will NOT be removed
            //  * input: none
            //  * output: none
            //  */
            // void deleteFrontPtr();
            // /**
            //  * delete the pointer to the Node at the end of the linked list (tail node)
            //  * the Tile object will NOT be removed
            //  * input: none
            //  * output: none
            //  */
            // void deleteBackPtr();

        /**
         * delete the the Node at the beginning of the linked list (head node)
         * the Tile object will be removed
         * input: none
         * output: none
         */
        void deleteFront();
        /**
         * delete the the Node at the end of the linked list (end node)
         * the Tile object will be removed
         * input: none
         * output: none
         */
        void deleteBack();

        /**
         * delete all the Nodes in the linked list
         * input: none
         * output: none
         */
        void clear();
        
        /**
         * return a COPY of Tile that is data of the head node
         * input: none
         * output: pointer (Tile*) to COPY of Tile
         */
        Tile* getFront();

        /**
         * return a COPY of Tile that is data of the tail node
         * input: none
         * output: pointer (Tile*) to COPY of Tile
         */
        Tile* getBack();

        /**
         * return a COPY of Tile using tile code, will copy the 1st Tile that has the same tileCode
         * input: tile code as std::string
         * output: pointer (Tile*) to COPY of Tile
         */
        Tile* getData(std::string tileCode);

        /**
         * delete a Node using tile code
         * input: tile code as std::string
         * output: none
         */
        void deleteData(std::string tileCode);

        /**
         * delete a Node at an index
         * input: index as int
         * output: none
         */
        void deleteIndex(int index);

    private:
        int size;
        Node* head;
        Node* tail;
};

#endif // LINKEDLIST_H