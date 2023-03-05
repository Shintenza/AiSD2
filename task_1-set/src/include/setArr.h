#pragma once
#include <iostream>
#include <cassert>

class setArr {
    int size;
    const int universeSize = 100;
    bool *table;
    bool checkRangeCorrectness(int x);
    int currentSize = 0;

public:
    setArr();
    setArr(int size);
    ~setArr() { delete [] table; table = nullptr; };
    void insert(int x);
    void withdraw(int x);
    bool isInSet(int i);
    int getSize();
    void clearSet();
    void printSet();
    setArr operator+(setArr &object);
    setArr operator*(setArr &object);
    setArr operator-(setArr &object);
    bool operator==(setArr &object);
    bool operator<=(setArr &object);

    bool equals(std::initializer_list<int> other);
};

