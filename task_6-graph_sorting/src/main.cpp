#include "include/matrix_graph.h"
#include <algorithm>
#include <climits>
#include <list>
#include <map>
#include <queue>

int main() {
    // MatrixGraph graph("./assets/Graf1.txt");
    // MatrixGraph graph("./assets/Graf2.txt");
    MatrixGraph graph(10);
    graph.addEdge(0, 1);
    graph.addEdge(1, 2);
    graph.addEdge(2, 0);
    graph.addEdge(3, 0);
    graph.addEdge(4, 1);
    graph.addEdge(5, 2);
    graph.addEdge(6, 5);

    std::vector<int> sortingResult = graph.topologicalSort();
    
    std::cout<<"Sorting result:"<<std::endl;
    for (int e : sortingResult) {
        std::cout<<e<<" ";
    }
    std::cout<<"\nIs acyclic: ";
    std::cout<<(sortingResult.size() == graph.getRealSize()) << std::endl;

}
