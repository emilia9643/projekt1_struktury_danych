#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <cstddef>

class DynamicArray {
public:
    DynamicArray();
    ~DynamicArray();

    size_t getSize() const;
    int getElement(size_t index) const;

    void add_back(int val);
    void add_front(int val);
    void add_at(size_t index, int val);

    void remove_back();
    void remove_front();
    void remove_at(size_t index);
    void clear();
    bool search(int val) const;

private:
    int* data;
    size_t capacity;
    size_t size;

    void resize(size_t new_capacity);
};

#endif // DYNAMIC_ARRAY_H
