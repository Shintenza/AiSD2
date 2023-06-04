#include <iostream>
#include "include/list_graph.h"

int main() {
    ListGraph graph("./assets/GrafZad2023.txt");
    std::cout<<graph.maxCut()<<std::endl;
}
