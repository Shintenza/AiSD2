#include "include/matrix_graph.h"
#include <algorithm>
#include <climits>
#include <list>
#include <map>
#include <queue>

int main() {
    // MatrixGraph graph("./assets/Graf1.txt");
    MatrixGraph graph("./assets/Graf2.txt");
    // MatrixGraph graph(6);
    // graph.addEdge(1, 4);
    // graph.addEdge(1, 2);
    // graph.addEdge(4, 2);
    // graph.addEdge(2, 3);
    // graph.addEdge(5, 3);

    std::vector<int> sortingResult = graph.topologicalSort();
    
    std::cout<<"Sorting result:"<<std::endl;
    for (int e : sortingResult) {
        std::cout<<e<<" ";
    }
    std::cout<<"\nIs acyclic: ";
    std::cout<<(sortingResult.size() == graph.getRealSize()) << std::endl;

}
