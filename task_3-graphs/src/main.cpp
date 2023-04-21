#include "include/list_graph.h"
#include "include/matrix_graph.h"
#include <cassert>

void test2() {
    MatrixGraph G("./assets/GTest.txt");
    
    std::cout << "sąsiedzi 0\n";
    G.printNeighbourIndices(0);
    std::cout << "sąsiedzi 7\n";
    G.printNeighbourIndices(7);
    std::cout << "sąsiedzi 9\n";
    G.printNeighbourIndices(9);
    std::cout << "vert degr 0\n";
    std::cout << G.vertexDegree(0) << "\n";
    std::cout << "vert degr 7\n";
    std::cout << G.vertexDegree(7) << "\n";
    std::cout << "vert degr 9\n";
    std::cout << G.vertexDegree(9) << "\n";
    std::cout << "liczba krawedzi \n";
    std::cout << G.getNumberOfEdges() << "\n\n";

}

int main() {
    // MatrixGraph graph("./assets/GrafSmall.txt");
    // ListGraph graph("./assets/GrafSmall.txt");
    // assert(graph.checkEdge(1, 2) && graph.checkEdge(2, 1));
    // assert(graph.checkEdge(2, 3) && graph.checkEdge(3, 2));
    //
    // std::vector<int> expextedZiomki = {2, 5, 10, 11, 12};
    // assert(expextedZiomki == graph.getNeighbourIndices(1));
    // graph.addEdge(1, 9);
    // assert(graph.checkEdge(1, 9) && graph.checkEdge(9, 1));
    // graph.removeEdge(1, 9);
    // assert(!graph.checkEdge(1, 9) && !graph.checkEdge(9, 1));
    //
    // assert(graph.vertexDegree(1) == 5);
    //
    // assert(graph.getNumberOfEdges() == 9);
    test2();

    return 0;
}
