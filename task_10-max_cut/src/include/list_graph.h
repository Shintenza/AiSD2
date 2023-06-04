#pragma once
#include "edge.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <array>

// implementacja grafu nieskierowanego na podstawie listy list

class ListGraph {
    std::vector<std::vector<Edge>> vertexList;

public:
    ListGraph() {};
    ListGraph(std::string dataPath);
    ListGraph(int initial_size) : vertexList(initial_size){};
    void addEdge(int i_Vertex_Index_1, int i_Vertex_Index_2);
    bool removeEdge(int i_Vertex_Index_1, int i_Vertex_Index_2);
    bool checkEdge(int i_Vertex_Index_1, int i_Vertex_Index_2);
    int vertexDegree(int idx);
    std::vector<int> getNeighbourIndices(int idx);
    void printNeighbourIndices(int idx);
    int getNumberOfEdges();
    void printGraph();

    std::array<int, 2> getInnerOuterEdges(int idx, std::vector<int> &partition);
    int maxCut();
};
