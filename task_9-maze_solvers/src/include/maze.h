#pragma once
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>

class Maze {
private:
    // std::vector<std::vector<int>> mazeVector;
    std::vector<int> mazeVector;
    int mazeWidth;
    int mazeHeight;

    int startingIndex;
    int endingIndex;

public:
    Maze(std::string data_path);
    int getVecSize() { return mazeVector.size(); }
    void printMaze();

    std::vector<int> getNeighbours(int idx, std::vector<bool> &visited);

    void BFS();
    void greedyOne();
    void aStarSearch();
};
