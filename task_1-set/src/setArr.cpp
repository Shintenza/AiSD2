#include "include/setArr.h"
#include <algorithm>
#include <stdexcept>

bool setArr::checkRangeCorrectness(int x) {
    if (x >= 0 && x < size)
        return true;
    return false;
}

setArr::setArr() {
    table = new bool[universeSize]();
    size = universeSize;
}

setArr::setArr(int size) : size(size) {
    table = new bool[size]();
}

void setArr::insert(int x) {
    if (!checkRangeCorrectness(x))
        throw std::invalid_argument("argument out of range");
    if (!table[x]) {
        table[x] = true;
        currentSize++;
    }
}

void setArr::withdraw(int x) {
    if (!checkRangeCorrectness(x))
        throw std::invalid_argument("argument out of range");
    if (table[x]) {
        table[x] = false;
        currentSize--;
    }
}

bool setArr::isInSet(int i) {
    if (!checkRangeCorrectness(i))
        throw std::invalid_argument("wrong argument");
    if (table[i])
        return true;
    return false;
}

int setArr::getSize() {
    return currentSize;
}

void setArr::clearSet() {
    for (int i = 0; i < size; i++)
        table[i] = false;
    currentSize = 0;
}

void setArr::printSet() {
    for (int i = 0; i < size; i++) {
        if (table[i])
            std::cout << i << " ";
    }
    std::cout << std::endl;
}

setArr setArr::operator+(setArr &other) {
    int maxSize = std::max(this->size, other.size);
    setArr resultSet(maxSize);

    for (int i = 0; i < maxSize; i++) {
        if (maxSize == this->size) {
            if (table[i] || (i < other.size && other.table[i]))
                resultSet.insert(i);
        } else {
            if (other.table[i] || (i < size && table[i]))
                resultSet.insert(i);
        }
    }

    return resultSet;
}

setArr setArr::operator*(setArr &other) {
    int minSize = std::min(this->size, other.size);
    setArr resultSet(minSize);

    for (int i = 0; i < minSize; i++) {
        if (this->table[i] && other.table[i])
            resultSet.insert(i);
    }

    return resultSet;
}

setArr setArr::operator-(setArr &other) {
    setArr resultSet(this->size);

    for (int i = 0; i < this->size; i++) {
        if (this->table[i] && !other.table[i]) 
            resultSet.insert(i);
    }

    return resultSet;
}

bool setArr::operator==(setArr &other) {
    int maxSize = std::max(this->size, other.size);
    int minSize = std::min(this->size, other.size);

    for (int i = 0; i < maxSize; i++) {
        if (i < minSize && this->table[i] != other.table[i])
            return false;
        if (i >= minSize && other.size > this->size && other.table[i])
            return false;
        if (i >= minSize && other.size < this->size && this->table[i])
            return false;
    }
    return true;
}

bool setArr::operator<=(setArr &other) {
    if ((other * (*this)) == other)
        return true;
    return false;
}

bool setArr::equals(std::initializer_list<int> other) {
    if (this->getSize() != (int) other.size())
        return false;
    int *tmp = new int[getSize()];
    int j = 0;

    for (int i = 0; i < size; i++) {
        if (table[i]) {
            tmp[j] = i;
            j++;
        }
    }

    j = 0;

    for (int e : other) {
        if (e != tmp[j])
            return false;
        j++;
    }

    return true;
}
