#include "include/test.h"

void Tests::testInsert() {
    testingSet.insert(1);
    testingSet.insert(1);
    testingSet.insert(5);
    testingSet.insert(6);
    testingSet.insert(9);
    testingSet.insert(10);
    testingSet.insert(10);
    testingSet.insert(11);

    assert(testingSet.getSize() == 6 && testingSet.equals({1, 5, 6, 9, 10, 11}));
}

void Tests::testWithdraw() {
    testingSet.withdraw(11);
    testingSet.withdraw(2);

    assert(testingSet.getSize() == 5 && testingSet.equals({1, 5, 6, 9, 10}));
}

void Tests::testIsInSet() {
    assert(testingSet.isInSet(9) && !testingSet.isInSet(2));
}

void Tests::testGetSize() {
    assert(testingSet.getSize() == 5);
}

void Tests::testClear() {
    setBst<int> tmp;
    tmp.insert(1);
    tmp.insert(2);
    tmp.insert(3);
    tmp.insert(4);

    tmp.clearSet();
    assert(tmp.getSize() == 0 && tmp.equals({}));
}

void Tests::testUnion() {
    setBst<int> tmp;
    tmp.insert(1);
    tmp.insert(2);
    tmp.insert(3);
    tmp.insert(4);
    tmp.insert(5);


    setBst<int> result = tmp + testingSet;
    setBst<int> result2 = testingSet + tmp;

    assert(result.getSize() == 8 && result.equals({1, 2, 3, 4, 5, 6, 9, 10}));
    assert(result2.getSize() == 8 && result2.equals({1, 2, 3, 4, 5, 6, 9, 10}));
}

void Tests::testIntersection() {
    setBst<int> tmp;
    
    tmp.insert(5);
    tmp.insert(6);
    tmp.insert(2);
    tmp.insert(4);

    setBst<int> result = tmp * testingSet;
    setBst<int> result2 = testingSet * tmp;
    assert(result.getSize() == 2 && result.equals({5, 6}));
    assert(result2.getSize() == 2 && result2.equals({5, 6}));
}

void Tests::testDiff() {
    setBst<int> tmp;
    tmp.insert(5);
    tmp.insert(6);
    tmp.insert(2);
    tmp.insert(4);

    setBst<int> result = testingSet - tmp;
    assert(result.getSize() == 3 && result.equals({1, 9, 10}));

    setBst<int> result2 = tmp - testingSet;
    assert(result2.getSize() == 2 && result2.equals({2, 4}));
    
}

void Tests::testSubset() {
    setBst<int> tmp;
    tmp.insert(5);
    tmp.insert(6);
    tmp.insert(2);
    tmp.insert(4);
    assert(!(testingSet<=tmp));

    tmp.withdraw(2);
    tmp.withdraw(4);
    assert(testingSet<=tmp);
}

void Tests::runTests() {
    std::cout<<"Uruchamianie testów"<<std::endl;
    testInsert();
    testWithdraw();
    testIsInSet();
    testGetSize();
    testClear();
    testUnion();
    testIntersection();
    testDiff();
    testSubset();
    std::cout<<"Testy zakończone pomyślnie"<<std::endl;
}
