#include <iostream>
#include "include/matrix_graph.h"

int main () {
    MatrixGraph graph("./assets/GrafZad.txt")  ;
    graph.floydWarshall();
    // graph.printMatrix();
    return 0;
}
