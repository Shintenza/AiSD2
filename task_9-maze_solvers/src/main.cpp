#include "include/maze.h"

int main () {
    Maze maze("./assets/labiryntG3.txt");
    std::cout<<"BFS"<<std::endl;
    maze.BFS();
    std::cout<<"Greedy"<<std::endl;
    maze.greedyOne();
    std::cout<<"A Star"<<std::endl;
    maze.aStarSearch();

    return 0;
}

