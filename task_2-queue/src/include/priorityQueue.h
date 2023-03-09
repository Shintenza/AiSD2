#pragma once
#include <stdexcept>
#include <iostream>
#include <cstring>
#include <cassert>

class PriorityQueue {
private:
    int msize;
    int *tab;
    int last = 0;

public:
    PriorityQueue(int size);
    PriorityQueue(const PriorityQueue &other);
    ~PriorityQueue() { delete[] tab; }

    PriorityQueue &operator=(const PriorityQueue &other);

    void insert(int x);
    int pop();
    void print(); 
    int getRootElem() const;
    bool empty() const { return last == 0; }
    int size() const { return last; }
    void clear();
    // for testing
    bool equals_raw(std::initializer_list<int> other);

private:
    int getParent(int i);
    int getLeftChild(int i);
    int getRightChild(int i);
    void heapifyUp(int i);
    void heapifyDown(int i);
};
