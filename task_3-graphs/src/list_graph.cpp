#include "include/list_graph.h"

ListGraph::ListGraph(std::string dataPath) {
    std::ifstream infile(dataPath);
    int tmp1, tmp2;
    infile>>tmp1;
    if (tmp1 <= 0) throw "invalid number of vertices";
    vertexList.resize(tmp1);

    while(infile >> tmp1 >> tmp2) {
        addEdge(tmp1, tmp2);
    }
}

void ListGraph::addEdge(int starting_index, int ending_index, int weight) {
    Edge edge(starting_index, ending_index, weight);

    if (starting_index >= vertexList.size()) {
        vertexList.resize(starting_index + 1);
        vertexList[starting_index].push_back(edge);
        return;
    }
    if (vertexList[starting_index].empty()) {
        vertexList[starting_index].push_back(edge);
        return;
    }

    int i = 0;
    while (i < vertexList[starting_index].size() && ending_index > vertexList[starting_index][i].getEndingVertex()) {
        i++;
    }

    if (vertexList[starting_index][i].getEndingVertex() == ending_index) {
        vertexList[starting_index][i] = edge;
        return;
    }

    vertexList[starting_index].insert(vertexList[starting_index].begin() + i, edge);
}

bool ListGraph::removeEdge(int starting_index, int ending_index) {
    if (starting_index >= vertexList.size())
        return false;

    int i = 0;
    while (i < vertexList[starting_index].size() && ending_index > vertexList[starting_index][i].getEndingVertex())
        i++;

    if (vertexList[starting_index][i].getEndingVertex() != ending_index)
        return false;

    vertexList[starting_index].erase(vertexList[starting_index].begin() + i);
    return true;
}

bool ListGraph::checkEdge(int starting_index, int ending_index) {
    bool found = false;

    for (Edge e : vertexList.at(starting_index)) {
        if (e.getEndingVertex() == ending_index) {
            found = true;
            break;
        }
    }

    return found;
}

int ListGraph::vertexDegree(int idx) {
    int deg = 0;
    for (Edge e : vertexList.at(idx)) {
        deg++;
    }
    return deg;
}


std::vector<int> ListGraph::getNeighbourIndices(int idx) {
    std::vector<int> results;

    for (Edge e : vertexList.at(idx)) {
        results.push_back(e.getEndingVertex());
    }
    return results;
}

void ListGraph::printNeighbourIndices(int idx) {
    if (vertexList.at(idx).empty()) return;
    for (Edge e : vertexList.at(idx)) {
        std::cout<<e.getEndingVertex()<<" ";
    }
    std::cout<<std::endl;
}

int ListGraph::getNumberOfEdges() {
    int edges = 0;
    for (std::size_t i = 0; i < vertexList.size(); i++) {
        edges += vertexList[i].size();
    }
    return edges;
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
