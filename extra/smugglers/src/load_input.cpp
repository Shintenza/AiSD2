#include "include/load_input.h"

void loadInput(int *&pricesArray, ListGraph &graph, ListGraph &transposedGraph) {
    int numberOfMetals;
    std::cin >> numberOfMetals;
    pricesArray = new int[numberOfMetals];

    for (int i = 0; i < numberOfMetals; i++) {
        std::cin >> pricesArray[i];
    }

    int numberOfEdges;
    std::cin >> numberOfEdges;

    int v1, v2, weight;
    for (int i = 0; i < numberOfEdges; i++) {
        std::cin >> v1 >> v2 >> weight;
        graph.addEdge(v1, v2, weight);
        transposedGraph.addEdge(v2, v1, weight);
    }
}
