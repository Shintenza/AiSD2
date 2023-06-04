#include <iostream>
#include "include/list_graph.h"

int main () {
    ListGraph graph("./assets/prim.txt");
    // ListGraph graph;
    // graph.addEdge(0, 1, 1);
    // graph.addEdge(1, 2, 2);
    // graph.addEdge(0, 3, 6);
    // graph.addEdge(3, 2, 9);
    // graph.addEdge(0, 2, 4);
    //
    // graph.addEdge(1, 0, 1);
    // graph.addEdge(2, 1, 2);
    // graph.addEdge(3, 0, 6);
    // graph.addEdge(2, 3, 9);
    // graph.addEdge(2, 0, 4);

    // graph.printGraph();

    graph.kruskal();
    graph.prim(5);
    return 0;
}
