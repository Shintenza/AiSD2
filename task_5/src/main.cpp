#include "include/matrix_graph.h"
#include <algorithm>
#include <climits>
#include <list>
#include <map>
#include <queue>

void dijkstra(MatrixGraph &graph, int src, int dest) {
    int graphSize = graph.getSize();
    int *prev = new int[graphSize]();
    int *dist = new int[graphSize]();

    // min priority_queue
    // pair <dist, vert>
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;

    for (int i = 0; i < graphSize; i++) {
        if (i == src) {
            dist[i] = 0;
            prev[i] = src;
        } else {
            dist[i] = INT_MAX;
            prev[i] = -1;
        }
    }
    pq.push({0, src});
    while (!pq.empty()) {
        int min = pq.top().second;
        pq.pop();
        std::vector<int> neighbours = graph.getNeighbourIndices(min);
        for (int neighbour : neighbours) {
            if (dist[neighbour] > dist[min] + graph.getEdgeValue(min, neighbour)) {
                dist[neighbour] = dist[min] + graph.getEdgeValue(min, neighbour);
                pq.push({dist[neighbour], neighbour});
                prev[neighbour] = min;
            }
        }
    }

    for (int i = 0; i < graphSize; i++) {
        std::cout << i << " : " << ((dist[i] == INT_MAX) ? -1 : dist[i]) << std::endl;
    }
    std::cout << std::endl;
    // finding the path

    std::list<int> answer;
    int last = dest;

    do {
        last = prev[last];
        answer.push_front(last);
    } while (last != src);

    std::cout << "path from " << src << " to " << dest << ": ";
    for (int e : answer) {
        std::cout << e << " ";
    }
    std::cout << std::endl;

    delete[] dist;
    delete[] prev;
}

int main() {
    MatrixGraph graph("./assets/GrafD.txt");
    dijkstra(graph, 7, 6);
}
