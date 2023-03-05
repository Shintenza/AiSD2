#pragma once
#include <iostream>
#include <vector>
#include <cassert>

// implementacja na podstawie drzewa BST z pierwszej części kursu
// https://github.com/Shintenza/AiSD/tree/master/zestaw11
template <typename T>
struct BSTNode {
    T value;
    BSTNode *left, *right;
    BSTNode *parent;
    BSTNode() : value(T()), left(nullptr), right(nullptr), parent(nullptr) {}
    BSTNode(const T &item) : value(item), left(nullptr), right(nullptr), parent(nullptr) {}
    ~BSTNode() {}
};

template <typename T>
class setBst {
    BSTNode<T> *root;
    int currentSize;

public:
    setBst() : root(nullptr), currentSize(0) {}
    ~setBst() { clearSet(); }
    void insert(const T &item) { root = insert(root, item); }
    void withdraw(const T &item);
    bool isInSet(const T &item) const;
    int getSize() const { return currentSize; };
    void clearSet();
    void printSet() {
        display(root);
        std::cout << std::endl;
    }
    setBst operator+(setBst<T> &other);
    setBst operator*(setBst<T> &other);
    setBst operator-(setBst<T> &other);
    bool operator==(setBst<T> &other);
    bool operator<=(setBst<T> &other);

    // testing
    bool equals(std::initializer_list<T> other);
    void inorder_testing(BSTNode<T> *node, std::vector<T> &v);

private:
    void clear(BSTNode<T> *node);
    BSTNode<T> *insert(BSTNode<T> *node, const T &item);
    BSTNode<T> *search(BSTNode<T> *node, const T &item) const;
    BSTNode<T> *remove(BSTNode<T> *node);
    void display(BSTNode<T> *node);

    void copy(BSTNode<T> *node, setBst<T> &other);
    void diff(BSTNode<T> *node, setBst<T> &other);
    void comm(BSTNode<T> *node, setBst<T> &other, setBst<T> &dest);
    void store(BSTNode<T> *node, std::vector<T> &v);
};

template <typename T>
setBst<T> setBst<T>::operator+(setBst<T> &other) {
    setBst<T> resultSet;

    this->copy(root, resultSet);
    other.copy(other.root, resultSet);
    return resultSet;
}

template <typename T>
setBst<T> setBst<T>::operator-(setBst<T> &other) {
    setBst<T> resultSet;
    this->copy(root, resultSet);
    resultSet.diff(other.root, other);
    return resultSet;
}

template <typename T>
setBst<T> setBst<T>::operator*(setBst<T> &other) {
    setBst<T> resultSet;
    if (this->getSize() < other.getSize()) {
        comm(this->root, other, resultSet);
    } else {
        comm(other.root, *this, resultSet);
    }

    return resultSet;
}

template <typename T>
bool setBst<T>::operator==(setBst<T> &other) {
    if (!(this->getSize() && other.getSize()))
        return false;
    std::vector<T> v1, v2;
    store(root, v1);
    store(other.root, v2);

    return (v1 == v2);
}

template <typename T>
bool setBst<T>::operator<=(setBst<T> &other) {
    if ((other * (*this)) == other)
        return true;
    return false;
}

template <typename T>
void setBst<T>::copy(BSTNode<T> *node, setBst<T> &other) {
    if (node == nullptr)
        return;
    copy(node->left, other);
    other.insert(node->value);
    copy(node->right, other);
}

template <typename T>
void setBst<T>::diff(BSTNode<T> *node, setBst<T> &other) {
    if (node == nullptr)
        return;
    diff(node->left, other);
    withdraw(node->value);
    diff(node->right, other);
}

template <typename T>
void setBst<T>::comm(BSTNode<T> *node, setBst<T> &other, setBst<T> &dest) {
    if (node == nullptr)
        return;
    comm(node->left, other, dest);
    if (other.isInSet(node->value))
        dest.insert(node->value);
    comm(node->right, other, dest);
}

template <typename T>
void setBst<T>::store(BSTNode<T> *node, std::vector<T> &v) {
    if (node == nullptr) return ;
    store(node->left, v);
    v.push_back(node->value);
    store(node->right, v);
}

template <typename T>
bool setBst<T>::isInSet(const T &item) const {
    auto ptr = search(root, item);
    return ((ptr == nullptr) ? false : true);
}

template <typename T>
void setBst<T>::clearSet() {
    clear(root);
    root = nullptr;
    currentSize = 0;
}

template <typename T>
void setBst<T>::display(BSTNode<T> *node) {
    if (node == nullptr)
        return;
    display(node->left);
    std::cout << node->value << " ";
    display(node->right);
}

template <typename T>
BSTNode<T> *setBst<T>::insert(BSTNode<T> *node, const T &item) {
    if (node == nullptr) {
        currentSize++;
        return new BSTNode<T>(item);
    }
    if (item < node->value) {
        node->left = insert(node->left, item);
        node->left->parent = node;
    } else if (item > node -> value){
        node->right = insert(node->right, item);
        node->right->parent = node;
    }
    return node;
}

template <typename T>
BSTNode<T> *setBst<T>::search(BSTNode<T> *node, const T &item) const {
    if (node == nullptr || node->value == item) {
        return node;
    } else if (item < node->value) {
        return search(node->left, item);
    } else {
        return search(node->right, item);
    }
}
template <typename T>
void setBst<T>::withdraw(const T &item) { // usuwanie przez złączanie
    // Najpierw znajdujemy wezel i jego rodzica.
    BSTNode<T> *node = root;
    BSTNode<T> *prev = nullptr;

    while (node != nullptr) {
        if (node->value == item)
            break;
        prev = node;
        if (item < node->value) {
            node = node->left;
        } else {
            node = node->right;
        }
    }
    // Szukamy przyczyny przerwania pętli while.
    if (node != nullptr && node->value == item) {
        // node ma być usunięty.
        if (node == root) {
            root = remove(node);
        } else if (prev->left == node) {
            prev->left = remove(node);
        } else {
            prev->right = remove(node);
        }
    } else if (root != nullptr) {
        ;    // klucza nie znaleziono
    } else { // root == nullptr
        ;    // drzewo jest puste
    }
}

template <typename T>
BSTNode<T> *setBst<T>::remove(BSTNode<T> *node) {
    assert(node != nullptr);
    BSTNode<T> *new_root;
    if (node->right == nullptr) {
        new_root = node->left;
    } else if (node->left == nullptr) { 
        new_root = node->right;
    } else {                             
        new_root = node;                 
        node = node->left;               
        while (node->right != nullptr) { 
            node = node->right;
        }
        node->right = new_root->right; 
        node = new_root;               
        new_root = node->left;         
    }
    delete node;
    currentSize--;
    return new_root;
}

template <typename T>
void setBst<T>::clear(BSTNode<T> *node) {
    if (node) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

template <typename T>
bool setBst<T>::equals(std::initializer_list<T> other) {
    std::vector<T> storage;

    inorder_testing(root, storage);

    if (storage.size() != other.size())
        return false;

    int i = 0;
    for (T el : other) {
        if (el != storage.at(i)) {
            return false;
        }
        i++;
    }
    return true;
}
 

template <typename T>
void setBst<T>::inorder_testing(BSTNode<T> *node, std::vector<T> &v) {
    if (node == nullptr)
        return;
    inorder_testing(node->left, v);
    v.push_back(node->value);
    inorder_testing(node->right, v);
}
