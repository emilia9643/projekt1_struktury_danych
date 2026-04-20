#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <cstddef>

class DoubleNode {
public:
    int element;
    DoubleNode* next_element;
    DoubleNode* prev_element; // Wskaźnik na poprzedni element

    DoubleNode(int val);
};

class DoublyLinkedList {
private:
    DoubleNode* head;
    DoubleNode* tail;
    size_t size;

public:
    DoublyLinkedList();
    ~DoublyLinkedList();

    bool isEmpty() const;
    size_t getSize() const;

    void addToFront(int element);
    void addAtEnd(int element);
    void addAtIndex(size_t index, int element);
    
    void removeFromBegining();
    void removeFromEnd();
    void removeAtIndex(size_t index);
    void clear();
    void display() const;
    bool isInList(int element) const;
};

#endif // DOUBLY_LINKED_LIST_H
