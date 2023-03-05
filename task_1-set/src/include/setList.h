#pragma once
#include <iostream>
#include <vector>

class setList {
    std::vector<int> vec;
    int currentSize;

public:
    setList() : currentSize(0){};
    ~setList() { vec.clear(); };
    int getSize() { return currentSize; };
    void printSet();
    void insert(int x);
    void withdraw(int x);
    void clearSet();
    bool isInSet(int x);
    setList operator+(setList &obj);
    setList operator*(setList &obj);
    setList operator-(setList &obj);
    bool operator==(setList &obj);
    bool operator<=(setList &obj);
    
    bool equals(std::initializer_list<int> other);
};
