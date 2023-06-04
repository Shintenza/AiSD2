#pragma once
#include "edge.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <climits>
#include <algorithm>


class ListGraph {
    std::vector<std::vector<Edge>> vertexList;
    std::map<int, bool> visited;
public:
    ListGraph() {};
    ListGraph(std::string dataPath);
    ListGraph(int initial_size) : vertexList(initial_size){};
    void addEdge(int i_Vertex_Index_1, int i_Vertex_Index_2, int weight = 1);
    bool removeEdge(int i_Vertex_Index_1, int i_Vertex_Index_2);
    bool checkEdge(int i_Vertex_Index_1, int i_Vertex_Index_2);
    int getEdgeWeight(int first_vertex, int second_vertex);
    int vertexDegree(int idx);
    int vertexInDegree(int idx);
    std::vector<int> getNeighbourIndices(int idx);
    std::vector<Edge> getOutEdges(int idx);
    void printOutEdges(int idx);
    void printNeighbourIndices(int idx);
    int getNumberOfEdges();
    void printGraph();

    void getEdges();

    bool isPresent(int idx);
    
    void DFS(int v, std::vector<int> &out);
    void BFS(int v, std::vector<int> &out);
    void dijkstra(int src);
    void floydWarshall();
    std::vector<int> topologicalSort();
    void kruskal();
    void prim(int starting_idx);
};
