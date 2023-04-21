#pragma once
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// graf nieskierowany 

class MatrixGraph {
    int **matrix;
    int numberOfVertices;

public:
    MatrixGraph(int vertNum);
    MatrixGraph(std::string dataPath);
    ~MatrixGraph();
    void addEdge(int first_vindex, int second_vindex, int weight = 1);
    bool removeEdge(int first_vindex, int second_vindex);
    bool checkEdge(int first_vindex, int second_vindex);
    int vertexDegree(int idx);
    std::vector<int> getNeighbourIndices(int idx);
    void printNeighbourIndices(int idx);
    int getNumberOfEdges();
    void printMatrix();
private:
    void clear();
};
