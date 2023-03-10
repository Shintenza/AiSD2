#pragma once
#include "priorityQueue.h"
#include <cassert>

class Test {
private:
    PriorityQueue testingQueue; 
    void testInsert();
    void testPop();
    void testGetRootElem();
    void testClear();
public:
    Test() : testingQueue(10) {};
    void runTests();
};
