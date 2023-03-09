#include "include/priorityQueue.h"

PriorityQueue::PriorityQueue(int size) : msize(size) {
    if (size <= 0)
        throw std::invalid_argument("Size has to be bigger than 0");
    tab = new int[msize];
}

PriorityQueue::PriorityQueue(const PriorityQueue &other) {
    tab = new int[other.msize];
    assert( tab != nullptr );
    memcpy(tab, other.tab, other.last * sizeof(int));
    
}

PriorityQueue &PriorityQueue::operator=(const PriorityQueue &other) {
    if (this == &other)
        return *this;
    delete[] tab;
    msize = other.msize;
    last = other.last;
    tab = new int[msize];
    assert(tab != nullptr);
    memcpy(tab, other.tab, msize * sizeof(int));
    return *this;
}

int PriorityQueue::getParent(int i) {
    if (i <= 0)
        throw std::invalid_argument("invalid index number");
    return (i - 1) / 2;
}

int PriorityQueue::getLeftChild(int i) {
    return (2 * i) + 1;
}

int PriorityQueue::getRightChild(int i) {
    return (2 * i) + 2;
}

void PriorityQueue::heapifyUp(int i) {
    while (i > 0 && tab[getParent(i)] < tab[i]) {
        std::swap(tab[getParent(i)], tab[i]);
        i = getParent(i);
    }
}

void PriorityQueue::heapifyDown(int i) {
    int maxIndex = i;

    int left = getLeftChild(i);
    if (left < last && tab[left] > tab[maxIndex]) {
        maxIndex = left;
    }

    int right = getRightChild(i);
    if (right < last && tab[right] > tab[maxIndex]) {
        maxIndex = right;
    }

    if (i != maxIndex) {
        std::swap(tab[i], tab[maxIndex]);
        heapifyDown(maxIndex);
    }
}

void PriorityQueue::insert(int x) {
    tab[last] = x;
    ++last;
    heapifyUp(last - 1);
}

int PriorityQueue::pop() {
    if (last - 1 < 0)
        throw std::invalid_argument("the queue is already empty");
    int rootElement = tab[0];

    tab[0] = tab[last - 1];
    tab[last - 1] = 0;
    last--;
    heapifyDown(0);
    return rootElement;
}

int PriorityQueue::getRootElem() const {
    if (last == 0) throw "the queue is empty";
    return tab[0];
}

void PriorityQueue::clear() {
    memset(tab, 0, last);
    last = 0;

}

void PriorityQueue::print() {
    for (int i = 0; i < last; i++) {
        std::cout << tab[i] << " ";
    }
    std::cout << std::endl;
}

bool PriorityQueue::equals_raw(std::initializer_list<int> other) {
    if (other.size() != (long unsigned int)size())
        return false;
    int i = 0;

    for (int el : other) {
        if (tab[i] != el) {
            return false;
        }
        i++;
    }
    return true;
}
