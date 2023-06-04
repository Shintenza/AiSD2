#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <iterator>

class KnapsackSolver {
private:
    int totalWeight;
    std::vector<std::pair<int,int>> loadedItems;
    int **matrix;
public:
    KnapsackSolver(std::string dataPath, int allowedWeight);
    void solve();
    ~KnapsackSolver();
    void printMatrix();
    void printLoadedItems();
};
