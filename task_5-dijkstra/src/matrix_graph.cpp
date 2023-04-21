#include "include/matrix_graph.h"

MatrixGraph::MatrixGraph(int vertNum) : numberOfVertices(vertNum) {
    matrix = new int *[vertNum];
    for (int i = 0; i < vertNum; i++)
        matrix[i] = new int[vertNum];
}

MatrixGraph::MatrixGraph(std::string dataPath) {
    std::ifstream infile(dataPath);
    int tmp1, tmp2, tmp3;
    infile >> tmp1;
    if (tmp1 <= 0)
        throw "invalid number of vertices";
    numberOfVertices = tmp1;

    matrix = new int *[numberOfVertices];
    for (int i = 0; i < numberOfVertices; i++)
        matrix[i] = new int[numberOfVertices];

    while (infile >> tmp1 >> tmp2 >> tmp3) {
        addEdge(tmp1, tmp2, tmp3);
    }
}

void MatrixGraph::clear() {
    for (int i = 0; i < numberOfVertices; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

MatrixGraph::~MatrixGraph() {
    clear();
}

void MatrixGraph::addEdge(int first_vindex, int second_vindex, int weight) {
    if (first_vindex < 0 || first_vindex >= numberOfVertices || second_vindex < 0 || second_vindex >= numberOfVertices || weight < 1)
        throw std::invalid_argument("wrong arguments");
    matrix[first_vindex][second_vindex] = weight > 1 ? weight : 1;
    // matrix[second_vindex][first_vindex] = weight > 1 ? weight : 1;
}

bool MatrixGraph::removeEdge(int first_vindex, int second_vindex) {
    if (first_vindex < 0 || first_vindex >= numberOfVertices || second_vindex < 0 || second_vindex >= numberOfVertices)
        throw std::invalid_argument("wrong arguments");

    if (matrix[first_vindex][second_vindex] > 0) {
        matrix[first_vindex][second_vindex] = 0;
        return true;
    }
    return false;
}

bool MatrixGraph::checkEdge(int first_vindex, int second_vindex) {
    if (first_vindex < 0 || first_vindex >= numberOfVertices || second_vindex < 0 || second_vindex >= numberOfVertices)
        throw std::invalid_argument("wrong arguments");

    if (matrix[first_vindex][second_vindex] > 0) {
        return true;
    }

    return false;
}

int MatrixGraph::vertexDegree(int idx) {
    int deg = 0;
    for (int i = 0; i < numberOfVertices; i++) {
        if (matrix[i][idx] > 0)
            deg++;
    }
    return deg;
}

std::vector<int> MatrixGraph::getNeighbourIndices(int idx) {
    std::vector<int> vec;
    for (int i = 0; i < numberOfVertices; i++) {
        if (matrix[idx][i] > 0)
            vec.push_back(i);
    }
    return vec;
}

void MatrixGraph::printNeighbourIndices(int idx) {
    for (int i = 0; i < numberOfVertices; i++) {
        if (matrix[idx][i])
            std::cout << i << " ";
    }
    std::cout << std::endl;
}

int MatrixGraph::getNumberOfEdges() {
    int edgesCounter = 0;
    for (int i = 0; i < numberOfVertices; i++) {
        for (int j = 0; j < numberOfVertices; j++) {
            if (matrix[i][j] > 0)
                edgesCounter++;
        }
    }
    return edgesCounter / 2;
}

void MatrixGraph::printMatrix() {
    for (int i = 0; i < numberOfVertices; i++) {
        for (int j = 0; j < numberOfVertices; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
