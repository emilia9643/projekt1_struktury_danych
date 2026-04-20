#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <cstddef>

class Node {
public:
    int element;
    Node* next_element;

    Node(int val); // Dodamy przydatny konstruktor wezla
};

class LinkedList {
private:
    Node* head;
    Node* tail;
    size_t size;

public:
    LinkedList();
    ~LinkedList();
    void clear();
    void display() const;
    bool isEmpty() const;
    size_t getSize() const; // Dodane, przydaje się do weryfikacji

    void addToFront(int element);
    void addAtEnd(int element);
    void addAtIndex(size_t index, int element);
    
    void removeFromBegining();
    void removeFromEnd();
    void removeAtIndex(size_t index);
    
    bool isInList(int element) const;
};

#endif // LINKED_LIST_H
