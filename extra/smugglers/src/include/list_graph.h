#pragma once
#include "edge.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <climits>

class ListGraph {
    std::vector<std::vector<Edge>> vertexList;

public:
    ListGraph() {};
    void addEdge(int firstIndex, int secondIndex, int weight = 1);
    std::vector<int> getNeighbourIndices(int idx);
    int getEdgeWeight(int v1, int v2);
    void printGraph();
    int getSize() { return vertexList.size(); }

    static std::vector<int> modified_dijkstra(ListGraph &graph, int src, int *&costs, bool transposed);
};
