#include "include/matrix_graph.h"
#include "include/list_graph.h"

int main () {
    ListGraph graph; 
    graph.addEdge(0, 1);
    graph.addEdge(1, 2);
    graph.addEdge(1, 3);
    graph.addEdge(2, 3);
    graph.printGraph();
    // std::cout<<graph.checkEdge(0,3)<<std::endl;
    // std::cout<<graph.vertexDegree(1)<<std::endl;
    graph.printNeighbourIndices(1);
    graph.printGraph();
    std::cout<<graph.getNumberOfEdges()<<std::endl;
    ListGraph testingGraph("/home/kamil/dev/aisd2/task_3/GrafL.txt");
    testingGraph.printGraph();

    return 0;
}
