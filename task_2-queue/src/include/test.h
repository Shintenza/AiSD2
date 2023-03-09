#pragma once
#include "priorityQueue.h"
#include <cassert>

class Test {
private:
    PriorityQueue testingQueue; 
    void testInsert();
    void testPop();
public:
    Test() : testingQueue(10) {};
    void runTests();
};
