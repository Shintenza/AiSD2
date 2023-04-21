#include "include/list_graph.h"
#include <cassert>

int main() {
    ListGraph graph("./assets/graf.txt");
    graph.printGraph();
    std::vector<int> out;
    std::vector<int> expected_out = {1, 36, 84, 21, 33, 17, 38, 30, 47, 66, 49};

    graph.DFS(1, out);

    for (auto e : out) {
        std::cout << e << " ";
    }

    // graph.DFS(1, out);
    // assert(out == expected_out);
    //
    // expected_out = {4};
    // out.clear();
    // graph.DFS(4, out);
    // assert(out == expected_out);
    //
    // expected_out = {7, 10};
    // out.clear();
    // graph.DFS(7, out);
    // assert(out == expected_out);
    //
    // expected_out = {11, 72, 57};
    // out.clear();
    // graph.DFS(11, out);
    // assert(out == expected_out);
    //
    //
    // expected_out = {1, 36, 84, 21, 66, 33, 49, 17, 30, 47, 38};
    // out.clear();
    // graph.BFS(1, out);
    // assert(out == expected_out);
    //
    // expected_out = {4};
    // out.clear();
    // graph.DFS(4, out);
    // assert(out == expected_out);
    //
    // expected_out = {7, 10};
    // out.clear();
    // graph.DFS(7, out);
    // assert(out == expected_out);
    //
    // expected_out = {11, 72, 57};
    // out.clear();
    // graph.DFS(11, out);
    // assert(out == expected_out);

    return 0;
}
