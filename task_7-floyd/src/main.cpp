#include <iostream>
#include "include/matrix_graph.h"

int main () {
    MatrixGraph graph("./assets/Graf1.txt")  ;
    graph.floydWarshall();
    // graph.printMatrix();
    return 0;
}
