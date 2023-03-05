#pragma once
#include "setArr.h"
#include "setList.h"

class Tests {
private:
    setList testingSet; 
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
