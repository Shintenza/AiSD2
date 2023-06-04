#include "include/list_graph.h"

ListGraph::ListGraph(std::string dataPath) {
    std::ifstream infile(dataPath);
    int tmp1, tmp2, tmp3;
    infile >> tmp1;
    if (tmp1 <= 0)
        throw "invalid number of vertices";

    while (infile >> tmp1 >> tmp2 >> tmp3) {
        addEdge(tmp1, tmp2, tmp3);
    }
}

void ListGraph::addEdge(int first_vertex, int second_vertex, int weight) {
    Edge edge(first_vertex, second_vertex, weight);

    if (first_vertex >= vertexList.size()) {
        vertexList.resize(first_vertex + 1);
        vertexList[first_vertex].push_back(edge);
        return;
    }
    if (vertexList[first_vertex].empty()) {
        vertexList[first_vertex].push_back(edge);
        return;
    }

    // vertexList[first_vertex].push_back(edge);

    int i = 0;
    while (i < vertexList[first_vertex].size() && second_vertex > vertexList[first_vertex][i].getEndingVertex()) {
        i++;
    }
    // if (vertexList[first_vertex][i].getEndingVertex() == second_vertex) {
    //     vertexList[first_vertex][i] = edge;
    //     return;
    // }
    //
    vertexList[first_vertex].insert(vertexList[first_vertex].begin() + i, edge);
}

bool ListGraph::removeEdge(int first_vertex, int second_vertex) {
    if (first_vertex >= vertexList.size())
        return false;

    int i = 0;
    while (i < vertexList[first_vertex].size() && second_vertex > vertexList[first_vertex][i].getEndingVertex())
        i++;

    if (vertexList[first_vertex][i].getEndingVertex() != second_vertex)
        return false;

    vertexList[first_vertex].erase(vertexList[first_vertex].begin() + i);
    return true;
}

bool ListGraph::checkEdge(int first_vertex, int second_vertex) {
    if (first_vertex >= vertexList.size())
        return false;

    for (Edge e : vertexList[first_vertex]) {
        if (e.getEndingVertex() == second_vertex)
            return true;
    }
    return false;
}

int ListGraph::getEdgeWeight(int first_vertex, int second_vertex) {
    if (first_vertex >= vertexList.size())
        return 0;

    for (Edge e : vertexList[first_vertex]) {
        if (e.getEndingVertex() == second_vertex) {
            return e.getWeight();
        }
    }
    return 0;
}

int ListGraph::vertexDegree(int idx) {
    int deg = 0;
    for (std::size_t i = 0; i < vertexList.size(); i++) {
        if (i != idx && checkEdge(i, idx)) {
            deg++;
        }
    }
    for (Edge e : vertexList[idx]) {
        deg++;
    }
    return deg;
}

int ListGraph::vertexInDegree(int idx) {
    int inDeg = 0;
    for (std::size_t i = 0; i < vertexList.size(); i++) {
        if (i != idx && checkEdge(i, idx)) {
            inDeg++;
        }
    }
    return inDeg;
}

std::vector<int> ListGraph::getNeighbourIndices(int idx) {
    if (idx >= vertexList.size())
        throw "out of range";
    std::vector<int> neighbours;
    for (Edge e : vertexList[idx]) {
        neighbours.push_back(e.getEndingVertex());
    }
    return neighbours;
}

std::vector<Edge> ListGraph::getOutEdges(int idx) {
    if (idx >= vertexList.size())
        throw "out of range";
    std::vector<Edge> out;
    for (Edge e : vertexList[idx]) {
        out.push_back(e);
    }
    return out;
}

void ListGraph::printOutEdges(int idx) {
    if (idx >= vertexList.size())
        throw "out of range";
    for (Edge e : vertexList[idx]) {
        std::cout<<"["<<e.getEndingVertex()<<" - "<< e.getWeight()<<"]"<<std::endl;
    }
}

void ListGraph::printNeighbourIndices(int idx) {
    if (idx >= vertexList.size())
        throw "out of range";

    for (Edge e : vertexList[idx]) {
        std::cout << e.getEndingVertex() << " ";
    }
    std::cout << std::endl;
}

int ListGraph::getNumberOfEdges() {
    int counter = 0;
    for (std::vector<Edge> v : vertexList) {
        counter += v.size();
    }
    return counter;
}

void ListGraph::printGraph() {
    for (std::size_t i = 0; i < vertexList.size(); i++) {
        std::cout << i << ": ";
        for (std::size_t j = 0; j < vertexList.at(i).size(); j++) {
            std::cout << vertexList[i][j].getEndingVertex() << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
};

void ListGraph::getEdges() {
    std::vector<Edge> edges;
    for (int i = 0; i < vertexList.size(); i++) {
        for (int j = 0; j < vertexList[i].size(); j++) {
            if (i > j) {
                edges.push_back(vertexList[i][j]);
            }
        }
    }

    for (Edge e : edges) {
        std::cout << e.getStartingVertex() << " " << e.getEndingVertex() << std::endl;
    }
}

bool ListGraph::isPresent(int idx) {
    if (idx >= vertexList.size())
        return false;
    if (vertexList[idx].size() > 0)
        return true;
    return false;
}

void ListGraph::DFS(int v, std::vector<int> &out) {
    visited[v] = true;
    out.push_back(v);
    for (int n : getNeighbourIndices(v)) {
        if (!visited[n]) {
            DFS(n, out);
        }
    }
}

void ListGraph::BFS(int v, std::vector<int> &out) {
    bool *visited = new bool[vertexList.size()]();
    std::queue<int> queue;

    queue.push(v);
    out.push_back(v);
    visited[v] = true;

    while (!queue.empty()) {
        int vertex = queue.front();
        queue.pop();

        for (int n : getNeighbourIndices(vertex)) {
            if (!visited[n]) {
                out.push_back(n);
                visited[n] = true;
                queue.push(n);
            }
        }
    }

    delete[] visited;
}

void ListGraph::dijkstra(int src) {
    int size = vertexList.size();
    int *dist = new int[size];
    int *prev = new int[size];

    // pair : <dist, vertex>
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;

    for (int i = 0; i < size; i++) {
        dist[i] = i != src ? INT_MAX : 0;
        prev[i] = 1 != src ? -1 : src;
    }

    pq.push({0, src});

    while (!pq.empty()) {
        int min = pq.top().second;
        pq.pop();

        for (int neighbour : getNeighbourIndices(min)) {
            if (dist[neighbour] > dist[min] + getEdgeWeight(min, neighbour)) {
                dist[neighbour] = dist[min] + getEdgeWeight(min, neighbour);
                pq.push({dist[neighbour], neighbour});
                prev[neighbour] = min;
            }
        }
    }

    // printing the answer
    for (int i = 0; i < size; i++) {
        std::cout << i << ": " << (dist[i] == INT_MAX ? -1 : dist[i]) << std::endl;
    }

    delete[] dist;
    delete[] prev;
}

std::vector<int> ListGraph::topologicalSort() {
    std::vector<int> out;
    std::queue<int> queue;
    int inDegreeCount[vertexList.size()];

    for (std::size_t i = 0; i < vertexList.size(); i++) {
        inDegreeCount[i] = vertexInDegree(i);
        if (inDegreeCount[i] == 0 && vertexList[i].size() > 0) {
            queue.push(i);
        }
    }

    while (!queue.empty()) {
        int vertex = queue.front();
        queue.pop();
        out.push_back(vertex);

        auto neighbours = getNeighbourIndices(vertex);

        for (int v : neighbours) {
            inDegreeCount[v]--;
            if (inDegreeCount[v] == 0) {
                queue.push(v);
            }
        }
    }
    return out;
}

void ListGraph::floydWarshall() {
    int size = vertexList.size();
    int **matrix = new int *[size];

    for (int i = 0; i < size; i++) {
        matrix[i] = new int[size];
        for (int j = 0; j < size; j++) {
            matrix[i][j] = i == j ? 0 : INT_MAX;
        }
    }

    for (int i = 0; i < size; i++) {
        for (Edge e : vertexList[i]) {
            matrix[i][e.getEndingVertex()] = e.getWeight();
        }
    }

    for (int k = 0; k < size; k++) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if ((matrix[i][j] > (matrix[i][k] + matrix[k][j])) && matrix[i][k] != INT_MAX && matrix[k][j] != INT_MAX) {
                    matrix[i][j] = matrix[i][k] + matrix[k][j];
                }
            }
        }
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
}

void ListGraph::kruskal() {
    std::priority_queue<Edge, std::vector<Edge>> pq;
    std::vector<int> vec;
    std::vector<Edge> mst;

    for (int i = 0; i < vertexList.size(); i++) {
        vec.push_back(i);
    }

    for (int i = 0; i < vertexList.size(); i++) {
        for (int j = 0; j < vertexList[i].size(); j++) {
            if (i > vertexList[i][j].getEndingVertex()) {
                pq.push(vertexList[i][j]);
            }
        }
    }

    // std::cout<<pq.size()<<std::endl;

    while (!pq.empty()) {
        Edge minEdge = pq.top();
        pq.pop();
        if (vec[minEdge.getStartingVertex()] == vec[minEdge.getEndingVertex()])
            continue;

        mst.push_back(minEdge);

        int min = std::min(vec[minEdge.getStartingVertex()], vec[minEdge.getEndingVertex()]);
        int max = std::max(vec[minEdge.getStartingVertex()], vec[minEdge.getEndingVertex()]);

        for (int i = 0; i < vec.size(); i++) {
            if (vec[i] == max) {
                vec[i] = min;
            }
        }
    }
    int weightSum = 0;

    for (Edge e : mst) {
        // std::cout<<e.getStartingVertex()<<" "<<e.getEndingVertex()<<" "<<e.getWeight()<<std::endl;
        weightSum += e.getWeight();
    }

    std::cout<<weightSum<<std::endl;
}

void ListGraph::prim(int starting_idx) {
    std::vector<int> visited; 
    std::priority_queue<Edge, std::vector<Edge>> pq;
    std::vector<Edge> mstEdges;

    visited.push_back(starting_idx);

    for (Edge e : getOutEdges(starting_idx)) {
        pq.push(e);
    }

    while (visited.size() < vertexList.size()) {
        Edge topEdge = pq.top();
        pq.pop();
        if (std::count(visited.begin(), visited.end(), topEdge.getEndingVertex())) continue;
        visited.push_back(topEdge.getEndingVertex());
        mstEdges.push_back(topEdge);

        for (Edge e : getOutEdges(topEdge.getEndingVertex())) {
            pq.push(e);
        }
    }


    int weightSum = 0;

    for (int v : visited) {
        std::cout<<v<<" ";
    }
    std::cout<<std::endl;
    for (Edge e : mstEdges) {
    //     std::cout<<e.getStartingVertex()<<" "<<e.getEndingVertex()<<" "<<e.getWeight()<<std::endl;
        weightSum += e.getWeight();
    }
    std::cout<<weightSum<<std::endl;
}
