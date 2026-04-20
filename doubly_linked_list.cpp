#include "doubly_linked_list.h"
#include<iostream>

DoubleNode::DoubleNode(int val) : element(val), next_element(nullptr), prev_element(nullptr) {}

DoublyLinkedList::DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

DoublyLinkedList::~DoublyLinkedList() {
    DoubleNode* current = head;
    while (current != nullptr) {
        DoubleNode* next = current->next_element;
        delete current;
        current = next;
    }
}

bool DoublyLinkedList::isEmpty() const {
    return head == nullptr;
}

size_t DoublyLinkedList::getSize() const {
    return size;
}
// dodajemy na front. 1. tworzymy nowy element newNode 2. gdy istnieją już jakieś elementy to żeby ustawić newNode jako pierwszy, najpierw ustawiamy newnode że następny element to aktualny head, potem aktualny head ustawiamy że poprzednik to newnode, na koniec ustawiamy newnode na head
void DoublyLinkedList::addToFront(int element) {
    DoubleNode* newNode = new DoubleNode(element);
    if (isEmpty()) {
        head = newNode;
        tail = newNode;
    } else {
        newNode->next_element = head;
        head->prev_element = newNode;
        head = newNode;
    }
    size++;
}
// analogicznie do powyższego
void DoublyLinkedList::addAtEnd(int element) {
    DoubleNode* newNode = new DoubleNode(element);
    if (isEmpty()) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next_element = newNode;
        newNode->prev_element = tail;
        tail = newNode;
    }
    size++;
}

void DoublyLinkedList::addAtIndex(size_t index, int element) {
    if (index == 0) {
        addToFront(element);
        return;
    }
    if (index >= size) {
        addAtEnd(element);
        return;
    }
    
    DoubleNode* newNode = new DoubleNode(element);
    DoubleNode* current;
    
    // sprawdzamy, z której strony jest bliżej do indeksu, ustawiamy current jako wskaźnik na head/tail i iterujemy x razy wskazując kolejno na następny/poprzedni element
    if (index < size / 2) {
        current = head;
        for (size_t i = 0; i < index - 1; ++i) {
            current = current->next_element;
        }
    } else {
        current = tail;
        for (size_t i = size - 1; i >= index; --i) {
            current = current->prev_element;
        }
    }
    
    // wstawiamy między current a current->next_element
    newNode->next_element = current->next_element;
    newNode->prev_element = current;
    
    current->next_element->prev_element = newNode;
    current->next_element = newNode;
    
    size++;
}

void DoublyLinkedList::removeFromBegining() {
    if (isEmpty()) return;

    DoubleNode* temp = head;
    head = head->next_element;
    
    if (head != nullptr) {
        head->prev_element = nullptr;
    } else {
        tail = nullptr; // Jeśli lista stała się pusta
    }
    
    delete temp;
    size--;
}

void DoublyLinkedList::removeFromEnd() {
    if (isEmpty()) return;

    DoubleNode* temp = tail;
    tail = tail->prev_element;
    
    if (tail != nullptr) {
        tail->next_element = nullptr;
    } else {
        head = nullptr; // Jeśli lista stała się pusta
    }
    
    delete temp;
    size--;
}

void DoublyLinkedList::removeAtIndex(size_t index) {
    if (isEmpty() || index >= size) return;
    
    if (index == 0) {
        removeFromBegining();
        return;
    }
    if (index == size - 1) {
        removeFromEnd();
        return;
    }
    
    DoubleNode* current;
    
    // Optymalizacja wyszukiwania (jak w addAtIndex)
    if (index < size / 2) {
        current = head;
        for (size_t i = 0; i < index; ++i) {
            current = current->next_element;
        }
    } else {
        current = tail;
        for (size_t i = size - 1; i > index; --i) {
            current = current->prev_element;
        }
    }
    
    // current to w tym momencie węzeł DO USUNIĘCIA
    current->prev_element->next_element = current->next_element;
    current->next_element->prev_element = current->prev_element;
    
    delete current;
    size--;
}

bool DoublyLinkedList::isInList(int element) const {
    DoubleNode* current = head;
    while (current != nullptr) {
        if (current->element == element) {
            return true;
        }
        current = current->next_element;
    }
    return false;
}

void DoublyLinkedList::clear() {
    DoubleNode* current = head;
    while (current != nullptr) {
        DoubleNode* next = current->next_element;
        delete current;
        current = next;
    }
    head = nullptr;
    tail = nullptr;
    size = 0;
}

void DoublyLinkedList::display() const {
    DoubleNode* current = head;
    while (current != nullptr) {
        std::cout << current->element << " ";
        current = current->next_element;
    }
    std::cout << "\n";
}