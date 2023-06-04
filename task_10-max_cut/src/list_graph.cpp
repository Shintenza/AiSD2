#include "include/list_graph.h"

ListGraph::ListGraph(std::string dataPath) {
    std::ifstream infile(dataPath);
    int tmp1, tmp2;
    infile >> tmp1;
    if (tmp1 <= 0)
        throw "invalid number of vertices";
    vertexList.resize(tmp1);

    while (infile >> tmp1 >> tmp2) {
        addEdge(tmp1, tmp2);
    }
}

void ListGraph::addEdge(int starting_index, int ending_index) {
    Edge edge(starting_index, ending_index);
    if ((long unsigned int)starting_index >= vertexList.size()) {
        vertexList.resize(starting_index + 1);
        vertexList.at(starting_index).push_back(edge);
        return addEdge(ending_index, starting_index);
    }
    auto it = vertexList.at(starting_index).begin();

    while (it != vertexList.at(starting_index).end() && it->getEndingVertex() < ending_index) {
        ++it;
    }

    // can't use iterator to check wheter element is there
    for (Edge e : vertexList.at(starting_index)) {
        if (e.getEndingVertex() == ending_index)
            return;
    }
    vertexList.at(starting_index).insert(it, edge);

    return addEdge(ending_index, starting_index);
}

bool ListGraph::removeEdge(int starting_index, int ending_index) {
    bool found = false;
    if (starting_index >= (int)vertexList.size() || ending_index >= (int)vertexList.size())
        return found;
    int idx = 0;

    for (Edge e : vertexList.at(starting_index)) {
        if (e.getEndingVertex() == ending_index) {
            found = true;
            break;
        }
        idx++;
    }

    if (!found)
        return found;
    std::vector<Edge> &vertex = vertexList.at(starting_index);
    vertex.erase(vertex.begin() + idx);

    idx = 0;
    for (Edge e : vertexList.at(ending_index)) {
        if (e.getEndingVertex() == starting_index) {
            break;
        }
        idx++;
    }

    std::vector<Edge> &secondVertex = vertexList.at(ending_index);
    secondVertex.erase(secondVertex.begin() + idx);

    return found;
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
    if (vertexList.at(idx).empty())
        return;
    for (Edge e : vertexList.at(idx)) {
        std::cout << e.getEndingVertex() << " ";
    }
    std::cout << std::endl;
}

int ListGraph::getNumberOfEdges() {
    int edges = 0;
    for (std::size_t i = 0; i < vertexList.size(); i++) {
        edges += vertexList[i].size();
    }
    return edges / 2;
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

std::array<int, 2> ListGraph::getInnerOuterEdges(int idx, std::vector<int> &partition) {
    std::array<int, 2> res;
    std::vector<int> neighbours = getNeighbourIndices(idx);
    int inner = 0;
    int crossing = 0;

    bool vertPart = partition[idx];

    for (int i = 0; i < neighbours.size(); i++) {
        if (partition[neighbours.at(i)] == vertPart)
            inner++;
        else
            crossing++;
    }

    res[0] = inner;
    res[1] = crossing;

    return res;
}

int ListGraph::maxCut() {
    srand((unsigned)time(0));

    int bestAnswer = 0;
    std::vector<int> bestPartition;
    std::vector<int> partition(vertexList.size());

    for (int i = 0; i < 500; i++) {
        for (int i = 0; i < partition.size(); i++) {
            partition[i] = rand() % 2;
        }

        bool condition = true;
        while (condition) {
            condition = false;
            for (int i = 0; i < vertexList.size(); i++) {
                std::array<int, 2> edgeCount = getInnerOuterEdges(i, partition);
                if (edgeCount[0] > edgeCount[1]) {
                    condition = true;
                    if (partition[i] == 1)
                        partition[i] = 0;
                    else
                        partition[i] = 1;
                }
            }
        }

        int crossingCounter = 0;

        for (int i = 0; i < vertexList.size(); i++) {
            crossingCounter += getInnerOuterEdges(i, partition)[1];
        }
        crossingCounter /= 2;

        if (crossingCounter > bestAnswer) {
            bestAnswer = crossingCounter;
            bestPartition = partition;
        }
    }

    for(int i : bestPartition) {
        std::cout<<i<<" ";
    }

    std::cout<<std::endl;

    return bestAnswer;
}
