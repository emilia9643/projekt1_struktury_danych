#include "dynamic_array.h"
#include <stdexcept>

DynamicArray::DynamicArray() : capacity(1), size(0) {
    data = new int[capacity];
}

DynamicArray::~DynamicArray() {
    delete[] data;
}

void DynamicArray::resize(size_t new_capacity) {
    int* new_data = new int[new_capacity];
    for (size_t i = 0; i < size; ++i) {
        new_data[i] = data[i];
    }
    delete[] data;
    data = new_data;
    capacity = new_capacity;
}

size_t DynamicArray::getSize() const {
    return size;
}

int DynamicArray::getElement(size_t index) const {
    if (index >= size) throw std::out_of_range("nie ma takiego indexu");
    return data[index];
}

void DynamicArray::add_back(int val) {
    if (size == capacity) {
        resize(capacity * 2); // Podwajamy pojemność, lepszy sposob niż +1
    }
    data[size++] = val;
}
//dodajemy na front, musimy przepisać wszystkie elementy do nowej tablicy
void DynamicArray::add_front(int val) {
    if (size == capacity) {
        resize(capacity * 2);
    }
    for (size_t i = size; i > 0; --i) {
        data[i] = data[i - 1];
    }
    data[0] = val;
    size++;
}

void DynamicArray::add_at(size_t index, int val) {
    if (index > size) throw std::out_of_range("nie ma takiego indexu");
    if (size == capacity) {
        resize(capacity * 2);
    }
    for (size_t i = size; i > index; --i) {
        data[i] = data[i - 1];
    }
    data[index] = val;
    size++;
}

void DynamicArray::remove_back() {
    if (size > 0) size--;
}

void DynamicArray::remove_front() {
    if (size == 0) return;
    for (size_t i = 0; i < size - 1; ++i) {
        data[i] = data[i + 1];
    }
    size--;
}

void DynamicArray::remove_at(size_t index) {
    if (index >= size) throw std::out_of_range("nie ma takiego indexu");
    for (size_t i = index; i < size - 1; ++i) {
        data[i] = data[i + 1];
    }
    size--;
}

bool DynamicArray::search(int val) const {
    for (size_t i = 0; i < size; ++i) {
        if (data[i] == val) return true;
    }
    return false;
}

void DynamicArray::clear() {
    delete[] data;
    capacity = 1;
    size = 0;
    data = new int[capacity];  
}