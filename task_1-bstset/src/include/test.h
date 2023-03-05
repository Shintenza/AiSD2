#pragma once
#include "setBst.h"
#include <cassert>

class Tests {
private:
    setBst<int> testingSet; 
    void testInsert();
    void testWithdraw();
    void testIsInSet();
    void testGetSize();
    void testClear();
    void testUnion();
    void testIntersection();
    void testDiff();
    void testSubset();

public:
    void runTests();
};
