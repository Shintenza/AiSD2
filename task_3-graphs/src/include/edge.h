#pragma once

class Edge {
private:
    int starting_vertex;
    int ending_vertex;
    float weight;

public:
    Edge(int first_vertex, int second_vertex, int weight = 1) : starting_vertex(first_vertex), ending_vertex(second_vertex), weight(weight){};
    int getStartingVertex() { return starting_vertex; };
    int getEndingVertex() { return ending_vertex; };
    float getWeight() { return weight; };
    bool operator==(Edge &other) {
        if (starting_vertex == other.starting_vertex && ending_vertex == other.ending_vertex && weight && other.weight)
            return true;
        return false;
    }
};
