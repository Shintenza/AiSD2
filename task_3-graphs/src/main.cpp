#include "include/list_graph.h"
#include "include/matrix_graph.h"
#include <cassert>

void testMatrixGraph() {
    std::cout<<"MatrixGraph"<<std::endl;
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

void testListGraph() {
    std::cout<<"ListGraph"<<std::endl;
    ListGraph G("./assets/GTest.txt");
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
    testMatrixGraph();
    testListGraph();

    return 0;
}
