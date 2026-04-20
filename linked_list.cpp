#include "linked_list.h"
#include <iostream>
using namespace std;
// Konstruktor węzła
Node::Node(int val) : element(val), next_element(nullptr) {}

// Konstruktor listy
LinkedList::LinkedList() : head(nullptr), tail(nullptr), size(0) {}

// Destruktor listy
LinkedList::~LinkedList() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next_element;
        delete current;
        current = next;
    }
}

bool LinkedList::isEmpty() const {
    return head == nullptr;
}

size_t LinkedList::getSize() const {
    return size;
}

void LinkedList::addToFront(int element) {
    Node* newNode = new Node(element);
    if (isEmpty()) {
        head = newNode;
        tail = newNode;
    } else {
        newNode->next_element = head;
        head = newNode;
    }
    size++;
}

void LinkedList::addAtEnd(int element) {
    Node* newNode = new Node(element);
    if (isEmpty()) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next_element = newNode;
        tail = newNode;
    }
    size++;
}

void LinkedList::removeFromBegining() {
    if (isEmpty()) return;

    Node* temp = head;
    head = head->next_element;
    delete temp;
    size--;

    if (head == nullptr) {
        tail = nullptr;
    }
}

void LinkedList::removeFromEnd() {
    if (isEmpty()) return;

    if (head == tail) { // Tylko jeden element w liscie
        delete head;
        head = nullptr;
        tail = nullptr;
    } else {
        Node* current = head;
        while (current->next_element != tail) {
            current = current->next_element;
        }
        delete tail;
        tail = current;
        tail->next_element = nullptr;
    }
    size--;
}

bool LinkedList::isInList(int element) const {
    Node* current = head;
    while (current != nullptr) {
        if (current->element == element) {
            return true;
        }
        current = current->next_element;
    }
    return false;
}

void LinkedList::addAtIndex(size_t index, int element) {
    if (index == 0) {
        addToFront(element);
        return;
    }
    if (index >= size) {
        addAtEnd(element);
        return;
    }
    
    Node* newNode = new Node(element);
    Node* current = head;
    for (size_t i = 0; i < index - 1; ++i) {
        current = current->next_element;
    }
    
    newNode->next_element = current->next_element;
    current->next_element = newNode;
    size++;
}

void LinkedList::removeAtIndex(size_t index) {
    if (isEmpty() || index >= size) return;
    
    if (index == 0) {
        removeFromBegining();
        return;
    }
    if (index == size - 1) {
        removeFromEnd();
        return;
    }
    
    Node* current = head;
    for (size_t i = 0; i < index - 1; ++i) {
        current = current->next_element;
    }
    
    Node* nodeToDelete = current->next_element;
    current->next_element = nodeToDelete->next_element;
    delete nodeToDelete;
    size--;
}
void LinkedList::clear() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next_element;
        delete current;
        current = next;
    }
    head = nullptr;
    tail = nullptr;
    size = 0;
}

void LinkedList::display() const {
    Node* current = head;
    while (current != nullptr) {
        std::cout << current->element << " ";
        current = current->next_element;
    }
    std::cout << "\n";
}