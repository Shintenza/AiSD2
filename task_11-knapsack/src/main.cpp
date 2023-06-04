#include <algorithm>
#include <iostream>
#include <vector>
#include <fstream>

#include "include/knapsack_solver.h"



int main () {
    KnapsackSolver solver("./assets/zadanie.txt", 25);
    // solver.printLoadedItems();
    solver.solve();
    // solver.printMatrix();

    
    return 0;
}
