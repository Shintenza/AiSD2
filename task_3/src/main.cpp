#include "include/matrix_graph.h"
#include "include/list_graph.h"
#include <cassert>

int main () {
    // MatrixGraph graph("./assets/GrafSmall.txt");
    ListGraph graph("./assets/GrafSmall.txt");
    assert(graph.checkEdge(1,2) && graph.checkEdge(2,1));
    assert(graph.checkEdge(2,3) && graph.checkEdge(3,2));

    std::vector<int> expextedZiomki = {2, 5, 10, 11, 12};
    assert(expextedZiomki == graph.getNeighbourIndices(1));
    graph.addEdge(1,9);
    assert(graph.checkEdge(1,9) && graph.checkEdge(9,1));
    graph.removeEdge(1,9);
    assert(!graph.checkEdge(1,9) && !graph.checkEdge(9,1));
    
    assert(graph.vertexDegree(1) == 5);
    
    assert(graph.getNumberOfEdges() == 9);

    return 0;
}
