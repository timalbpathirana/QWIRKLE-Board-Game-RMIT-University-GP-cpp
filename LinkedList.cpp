#include "LinkedList.h"
#include "Node.h"

LinkedList::LinkedList() {
    head = nullptr;
    tail = nullptr;
    size = 0;
};
LinkedList::~LinkedList() {
    clear();
};

int LinkedList::getSize() {
    return size;
};

Tile* LinkedList::getIndex(int index) {
    int currentIndex = 0;
    Node* currentNode = head;
    while (currentIndex != index) {
        //currentNode = currentNode->next;
        currentNode = currentNode->getNext();
        currentIndex++;
    }
    // return currentNode->data;
    return currentNode->getData();
};

void LinkedList::addFront(Tile* data) {
    if (head == nullptr) {
        head = new Node(data, nullptr, nullptr);
        tail = head;
    } else {
        // head->prev = new Node(data, head, nullptr);
        head->setPrevious(new Node(data, head, nullptr));
        head = head->getPrevious();
    }
    size++;
};
void LinkedList::addBack(Tile* data) {
    if (tail == nullptr) {
        tail = new Node(data, nullptr, nullptr);
        head = tail;
    } else {
        // tail->next = new Node(data, nullptr, tail);
        tail->setNext(new Node(data, nullptr, tail));
        // tail = tail->next;
        tail = tail->getNext();
    }
    size++;
};

// void LinkedList::deleteFrontPtr() {
//     // Node* toDelete = head;
//     head = head->next;
//     head->prev = nullptr;
//     // delete toDelete; 
//     size--;
// };
// void LinkedList::deleteBackPtr() {
//     // Node* toDelete = tail;
//     tail = tail->prev;
//     tail->next = nullptr;
//     // delete toDelete;
//     size--;
// };

void LinkedList::deleteFront() {
    Node* toDelete = head;
    if (head->getNext() != nullptr) {
        head = head->getNext();
        head->setPrevious(nullptr);
    }
    delete toDelete; 
    size--;
    if (size == 0) {
        head = nullptr;
        tail = nullptr;
    }
};
void LinkedList::deleteBack() {
    Node* toDelete = tail;
    if (tail->getPrevious() != nullptr) {
        tail = tail->getPrevious();
        tail->setNext(nullptr);
    }
    delete toDelete;
    size--;
    if (size == 0) {
        head = nullptr;
        tail = nullptr;
    }
};

void LinkedList::clear() {
    Node* current = head;
    Node* toDelete = nullptr;
    while (current != nullptr) {
        toDelete = current;
        // current = current->next;
        current = current->getNext();
        delete toDelete;
        size--;
    }
    head = nullptr;
    tail = nullptr;
}

Tile* LinkedList::getData(std::string tileCode) {
    Tile* toReturn = nullptr;
    int count = 0;
    Node* current = head;
    while (count < size && current->getData()->getTileCode() != tileCode) {
        current = current->getNext();
        count++;
    }
    if (count < size) {
        toReturn = new Tile(*current->getData());
    }
    return toReturn;
}

void LinkedList::deleteData(std::string tileCode) {
    Node* toDelete = nullptr;
    int count = 0;
    Node* current = head;
    while (count < size && current->getData()->getTileCode() != tileCode) {
        current = current->getNext();
        count++;
    }
    if (count < size) {
        toDelete = current;
    }
    
    if (toDelete == head) {
        if (head->getNext() != nullptr) {
            head = head->getNext();
            head->setPrevious(nullptr);
        }
    } else if (toDelete == tail) {
        if (tail->getPrevious() != nullptr) {
            tail = tail->getPrevious();
            tail->setNext(nullptr);
        }
    } else {
        toDelete->getPrevious()->setNext(toDelete->getNext());
        toDelete->getNext()->setPrevious(toDelete->getPrevious());
    }
    size--;
    delete toDelete;
    if (size == 0) {
        head = nullptr;
        tail = nullptr;
    }
}

void LinkedList::deleteIndex(int index) {
    if (index >= 0 && index < size) {
        Node* toDelete = head;
        int currentIndex = 0;
        while (currentIndex < index) {
            toDelete = toDelete->getNext();
            currentIndex++;
        }

        if (toDelete == head) {
            if (head->getNext() != nullptr) {
                head = head->getNext();
                head->setPrevious(nullptr);
            }
        } else if (toDelete == tail) {
            if (tail->getPrevious() != nullptr) {
                tail = tail->getPrevious();
                tail->setNext(nullptr);
            }
        } else {
            toDelete->getPrevious()->setNext(toDelete->getNext());
            toDelete->getNext()->setPrevious(toDelete->getPrevious());
        }
        size--;
        delete toDelete;
    }

    if (size == 0) {
        head = nullptr;
        tail = nullptr;
    }
}

Tile* LinkedList::getFront() {
    Tile* toReturn = nullptr;
    if (head != nullptr) {
        toReturn = new Tile(*head->getData());
    }
    return toReturn;
}

Tile* LinkedList::getBack() {
    Tile* toReturn = nullptr;
    if (tail != nullptr) {
        toReturn = new Tile(*tail->getData());
    }
    return toReturn;
}