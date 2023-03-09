#include "include/test.h"

void Test::testInsert() {
    testingQueue.insert(10);
    testingQueue.insert(14);
    testingQueue.insert(1);
    testingQueue.insert(13);
    testingQueue.insert(4);
    testingQueue.insert(6);

    assert(testingQueue.size() == 6 && testingQueue.equals_raw({14, 13, 6, 10, 4, 1}));
}

void Test::testPop() {
    assert(testingQueue.pop() == 14 && testingQueue.size() == 5 && testingQueue.equals_raw({13, 10, 6, 1, 4}));
    assert(testingQueue.pop() == 13 && testingQueue.size() == 4 && testingQueue.equals_raw({10, 4, 6, 1}));
    assert(testingQueue.pop() == 10 && testingQueue.size() == 3 && testingQueue.equals_raw({6, 4, 1}));
}

void Test::runTests() {
    std::cout<<"Uruchamianie testów..."<<std::endl;
    testInsert();
    testPop();
    std::cout<<"Testy zakończone pomyślnie"<<std::endl;
}
