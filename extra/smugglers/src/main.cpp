#include "include/list_graph.h"
#include "include/load_input.h"
#include <queue>

/*Program od razu po uruchomieniu oczekuje na wejście, a następnie w pierwszej linijce wyjścia podaje odpowiedź*/

int main() {
    int *metalPrices;
    ListGraph graph;
    ListGraph transposedGraph;

    loadInput(metalPrices, graph, transposedGraph);

    if (graph.getSize() == 0) {
        std::cout << metalPrices[0] / 2 << std::endl;
        return 0;
    }

    std::vector<int> costToVertices = ListGraph::modified_dijkstra(graph, 1, metalPrices, false);
    std::vector<int> costFromVertices = ListGraph::modified_dijkstra(transposedGraph, 1, metalPrices, true);

    int min = INT_MAX;
    for (std::size_t i = 0; i < costToVertices.size(); i++) {
        int sum = (costToVertices[i] == INT_MAX || costFromVertices[i] == INT_MAX) ? INT_MAX : costToVertices[i] + costFromVertices[i];
        if (sum < min)
            min = sum;
    }

    std::cout << min << std::endl;

    delete[] metalPrices;
}
