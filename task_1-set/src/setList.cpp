#include "include/setList.h"

void setList::printSet() {
    for (int i = 0; i < currentSize; i++) {
        std::cout << vec.at(i) << " ";
    }
    std::cout << std::endl;
}

void setList::insert(int x) {
    if (currentSize == 0) {
        vec.push_back(x);
        currentSize++;
        return;
    }
    int pos = 0;
    for (int i = 0; i < currentSize; i++) {
        if (vec[i] == x)
            return;
    }
    while (pos < currentSize && vec.at(pos) < x) {
        pos++;
    }
    vec.insert(vec.begin() + pos, x);
    currentSize++;
}

void setList::withdraw(int x) {
    auto it = vec.begin();

    while (it != vec.end() && *it < x) {
        ++it;
    }
    if (*it != x)
        return;
    vec.erase(it);
    currentSize--;
}

void setList::clearSet() {
    vec.clear();
    currentSize = 0;
}

bool setList::isInSet(int x) {
    auto it = vec.begin();

    while (it != vec.end() && *it < x) {
        ++it;
    }
    if (*it == x)
        return true;

    return false;
}

setList setList::operator+(setList &other) {
    setList resultList;

    auto thisIt = this->vec.begin();
    auto otherIt = other.vec.begin();

    while (thisIt != this->vec.end() && otherIt != other.vec.end()) {
        // std::cout << "DEBUG: " << *thisIt << " " << *otherIt << std::endl;
        if (*thisIt < *otherIt) {
            if (resultList.vec.empty() || resultList.vec.back() != *thisIt) {
                resultList.vec.push_back(*thisIt);
                resultList.currentSize++;
            }
            ++thisIt;
        } else {
            if (resultList.vec.empty() || resultList.vec.back() != *otherIt) {
                resultList.vec.push_back(*otherIt);
                resultList.currentSize++;
            }
            ++otherIt;
        }
    }

    while (thisIt != this->vec.end()) {
        if (resultList.vec.back() != *thisIt) {
            resultList.vec.push_back(*thisIt);
            resultList.currentSize++;
        }
        ++thisIt;
    }

    while (otherIt != other.vec.end()) {
        if (resultList.vec.back() != *otherIt) {
            resultList.vec.push_back(*otherIt);
            resultList.currentSize++;
        }
        ++otherIt;
    }

    return resultList;
}

setList setList::operator*(setList &other) {
    setList resultSet;

    auto thisIt = this->vec.begin();
    auto otherIt = other.vec.begin();

    while (thisIt != this->vec.end() && otherIt != other.vec.end()) {
        if (*thisIt == *otherIt) {
            resultSet.vec.push_back(*thisIt);
            resultSet.currentSize++;
            ++thisIt;
            ++otherIt;
        } else if (*thisIt < *otherIt) {
            ++thisIt;
        } else {
            ++otherIt;
        }
    }

    return resultSet;
}

setList setList::operator-(setList &other) {
    setList resultSet;

    auto thisIt = this->vec.begin();
    auto otherIt = other.vec.begin();

    while (thisIt != this->vec.end() && otherIt != other.vec.end()) {
        if (*thisIt == *otherIt) {
            ++thisIt;
            ++otherIt;
        } else if (*thisIt < *otherIt) {
            resultSet.vec.push_back(*thisIt);
            resultSet.currentSize++;
            ++thisIt;
        } else {
            ++otherIt;
        }
    }

    while (thisIt != this->vec.end()) {
        resultSet.vec.push_back(*thisIt);
        resultSet.currentSize++;
        ++thisIt;
    }

    return resultSet;
}

bool setList::operator==(setList &other) {
    if (this->getSize() != other.getSize())
        return false;
    auto thisIt = this->vec.begin();
    auto otherIt = other.vec.begin();

    while (thisIt != this->vec.end() && otherIt != other.vec.end()) {
        if (*thisIt != *otherIt)
            return false;
        ++thisIt;
        ++otherIt;
    }

    return true;
}

bool setList::operator<=(setList &other) {
    if ((other * (*this)) == other)
        return true;
    return false;
}

bool setList::equals(std::initializer_list<int> other) {
    if (this->getSize() != (int) other.size())
        return false;

    int i = 0;

    for (int e : other) {
        if (e != vec[i])
            return false;
        i++;
    }

    return true;
}
