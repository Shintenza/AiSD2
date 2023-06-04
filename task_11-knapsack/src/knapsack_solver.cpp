#include "include/knapsack_solver.h"

KnapsackSolver::KnapsackSolver(std::string dataPath, int allowedWeight) : totalWeight(allowedWeight) {
    std::ifstream inputFile(dataPath);

    int weight, value;

    while (inputFile >> weight >> value) {
        loadedItems.push_back({weight, value});
    }

    matrix = new int *[loadedItems.size() + 1];
    for (int i = 0; i < loadedItems.size() + 1; i++) {
        matrix[i] = new int[totalWeight + 1]();
    }
}

void KnapsackSolver::solve() {
    // adding the first item
    for (int i = loadedItems[0].first; i < totalWeight + 1; i++) {
        matrix[1][i] = loadedItems[0].second;
    }

    // adding the rest of items
    for (int i = 2; i < loadedItems.size() + 1; i++) {
        auto currentItem = loadedItems[i - 1];
        for (int j = 1; j < totalWeight + 1; j++) {
            if (currentItem.first > j) {
                matrix[i][j] = matrix[i - 1][j];
            } else {
                matrix[i][j] = std::max(matrix[i - 1][j], matrix[i - 1][j - currentItem.first] + currentItem.second);
            }
        }
    }

    // time for figuring out which items were added
    
    std::vector<int> includedItems;
    std::cout<<matrix[loadedItems.size()][totalWeight]<<std::endl;

    int profitLeft = matrix[loadedItems.size()][totalWeight];
    for (int i = loadedItems.size(); i > 0; i--) {
        auto currentItem = loadedItems[i-1];
        if (std::binary_search(matrix[i], matrix[i] + totalWeight +1, profitLeft) && !std::binary_search(matrix[i-1], matrix[i-1]+totalWeight+1, profitLeft)) {
            profitLeft-=currentItem.second;
            includedItems.push_back(i);
        }
    }

    for (int i : includedItems) {
        std::cout<<i<<" ";
    }

    std::cout<<std::endl;


}

KnapsackSolver::~KnapsackSolver() {
    for (int i = 0; i < loadedItems.size() + 1; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

void KnapsackSolver::printMatrix() {
    for (int i = 0; i < loadedItems.size() + 1; i++) {
        for (int j = 0; j < totalWeight + 1; j++) {
            std::cout << std::setw(3) << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void KnapsackSolver::printLoadedItems() {
    for (auto item : loadedItems) {
        std::cout<<"W: "<<item.first<<" "<<"V: "<<item.second<<std::endl;
    }
}
