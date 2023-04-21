#include "include/list_graph.h"

void ListGraph::addEdge(int starting_index, int ending_index, int weight) {
    Edge edge(starting_index, ending_index, weight);

    if ((long unsigned int)starting_index >= vertexList.size()) {
        vertexList.resize(starting_index + 1);
        vertexList.at(starting_index).push_back(edge);
    }
    auto it = vertexList.at(starting_index).begin();

    while (it != vertexList.at(starting_index).end() && it->getEndingVertex() < ending_index) {
        ++it;
    }

    for (Edge e : vertexList.at(starting_index)) {
        if (e.getEndingVertex() == ending_index)
            return;
    }
    vertexList.at(starting_index).insert(it, edge);
}

int ListGraph::getEdgeWeight(int v1, int v2) {
    if (vertexList.empty())
        return 0;
    std::vector<Edge> neighbours = vertexList.at(v1);
    for (Edge e : neighbours) {
        if (e.getEndingVertex() == v2) {
            return e.getWeight();
        }
    }
    return 0;
}
std::vector<int> ListGraph::getNeighbourIndices(int idx) {
    std::vector<int> results;
    if (vertexList.empty()) return results;

    for (Edge e : vertexList.at(idx)) {
        results.push_back(e.getEndingVertex());
    }
    return results;
}

void ListGraph::printGraph() {
    for (std::size_t i = 0; i < vertexList.size(); i++) {
        std::cout << "Vertex nr. " << i << ": ";
        for (std::size_t j = 0; j < vertexList.at(i).size(); j++) {
            std::cout << vertexList.at(i).at(j).getEndingVertex() << " ";
        }
        std::cout << std::endl;
    }
}

std::vector<int> ListGraph::modified_dijkstra(ListGraph &graph, int src, int *&costs, bool transposed) {
    std::vector<int> cost;
    int graphSize = graph.getSize();
    int *prev = new int[graphSize]();
    int *dist = new int[graphSize]();

    int *lowestCostMaterial = new int[graphSize]();

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
            int edgeValue = graph.getEdgeWeight(min, neighbour);
            if (dist[neighbour] > dist[min] + edgeValue) {
                dist[neighbour] = dist[min] + edgeValue;
                pq.push({dist[neighbour], neighbour});
                prev[neighbour] = min;
            }
        }
    }

    if (!transposed) {
        for (int i = 0; i < graphSize; i++) {
            if (dist[i] == INT_MAX) {
                lowestCostMaterial[i] = INT_MAX;
                continue;
            }
            int last = i;
            int min = costs[i - 1];
            do {
                last = prev[last];
                if (min > costs[last - 1]) {
                    min = costs[last - 1];
                }
            } while (last != src);
            lowestCostMaterial[i] = min / 2;
        }
    }

    for (int i = 0; i < graphSize; i++) {
        int sum;
        if (dist[i] == INT_MAX || lowestCostMaterial[i] == INT_MAX)
            sum = INT_MAX;
        else
            sum = dist[i] + lowestCostMaterial[i];
        cost.push_back(sum);
    }

    delete[] dist;
    delete[] prev;
    delete[] lowestCostMaterial;
    return cost;
}
