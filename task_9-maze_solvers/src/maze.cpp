#include "include/maze.h"
#include <algorithm>
#include <random>

Maze::Maze(std::string data_path) {
    std::ifstream inputFile(data_path);
    std::string line, singleEntry;

    int height = 0;
    int width = 0;

    while (std::getline(inputFile, line)) {
        std::stringstream str(line);
        while (std::getline(str, singleEntry, ';')) {
            int intEntry = std::stoi(singleEntry);
            mazeVector.push_back(std::stoi(singleEntry));
            if (intEntry == 2)
                startingIndex = width;
            if (intEntry == 3)
                endingIndex = width;
            ++width;
        }
        ++height;
    }

    mazeWidth = width / height;
    mazeHeight = height;
}

void Maze::printMaze() {
    for (int i = 0; i < mazeHeight * mazeWidth; i++) {
        std::cout << mazeVector[i] << " ";
        if ((i + 1) % mazeWidth == 0) {
            std::cout << std::endl;
        }
    }
}

std::vector<int> Maze::getNeighbours(int idx, std::vector<bool> &visited) {
    std::vector<int> neighbours;
    auto index = [&](int x, int y) {
        return idx + x + y * mazeWidth;
    };

    // std::cout<<(index(0, -1) > 0 && mazeVector[index(0, -1)] > 0 && !visited[index(0, -1)])<<std::endl;

    if (index(0, -1) >= 0 && mazeVector[index(0, -1)] > 0 && !visited[index(0, -1)])
        neighbours.push_back(index(0, -1));
    if ((idx + 1) % mazeWidth != 0 && mazeVector[index(1, 0)] > 0 && !visited[index(1, 0)])
        neighbours.push_back(index(1, 0));
    if (index(0, 1) < mazeVector.size() && mazeVector[index(0, 1)] > 0 && !visited[index(0, 1)])
        neighbours.push_back(index(0, 1));
    if (idx % mazeWidth != 0 && mazeVector[index(-1, 0)] > 0 && !visited[index(-1, 0)])
        neighbours.push_back(index(-1, 0));

    return neighbours;
}

void Maze::BFS() {
    std::queue<int> queue;
    std::vector<bool> visited(getVecSize());
    std::vector<int> prev(getVecSize());

    int visitedCounter = 0;
    int pathSize = 0;

    prev[startingIndex] = startingIndex;
    queue.push(startingIndex);

    while (!queue.empty()) {
        int currentIndex = queue.front();
        queue.pop();

        if (currentIndex == endingIndex)
            break;

        visited[currentIndex] = true;
        visitedCounter++;

        // for DFS this vector ought to be shuffled
        std::vector<int> neighbours = getNeighbours(currentIndex, visited);

        for (int neighbourIdx : neighbours) {
            prev[neighbourIdx] = currentIndex;
            queue.push(neighbourIdx);
        }
    }

    int last = endingIndex;

    do {
        last = prev[last];
        pathSize++;
    } while (last != startingIndex);

    std::cout << "visited: " << visitedCounter << std::endl;
    std::cout << "path size: " << pathSize << std::endl;
}

void Maze::greedyOne() {
    std::vector<int> dist;
    std::vector<bool> visited(getVecSize());
    std::vector<int> prev(getVecSize());

    int visitedCounter = 0;
    int pathSize = 0;

    for (int i = 0; i < getVecSize(); i++) {
        int yDist = std::abs(endingIndex / mazeWidth - i / mazeWidth);
        int xDist = i == 0 ? mazeWidth : mazeWidth - (i % mazeWidth);

        dist.push_back(xDist + yDist - 1);
    }

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;

    prev[startingIndex] = startingIndex;
    pq.push({dist[startingIndex], startingIndex});

    while (!pq.empty()) {
        int currentIndex = pq.top().second;
        pq.pop();

        if (currentIndex == endingIndex)
            break;

        visited[currentIndex] = true;
        visitedCounter++;

        // for DFS this vector ought to be shuffled
        std::vector<int> neighbours = getNeighbours(currentIndex, visited);

        for (int neighbourIdx : neighbours) {
            prev[neighbourIdx] = currentIndex;
            pq.push({dist[neighbourIdx], neighbourIdx});
        }
    }

    int last = endingIndex;

    do {
        last = prev[last];
        pathSize++;
    } while (last != startingIndex);

    std::cout << "visited: " << visitedCounter + 1<< std::endl;
    std::cout << "path size: " << pathSize << std::endl;
}

void Maze::aStarSearch() {
    std::vector<int> dist;
    std::vector<int> distToStart(getVecSize(), 0);
    std::vector<bool> visited(getVecSize());
    std::vector<int> prev(getVecSize());

    int visitedCounter = 0;
    int pathSize = 0;

    for (int i = 0; i < getVecSize(); i++) {
        int yDist = std::abs(endingIndex / mazeWidth - i / mazeWidth);
        int xDist = i == 0 ? mazeWidth : mazeWidth - (i % mazeWidth);

        dist.push_back(xDist + yDist - 1);
    }

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;

    prev[startingIndex] = startingIndex;
    distToStart[startingIndex] = 0;
    pq.push({dist[startingIndex] + 0, startingIndex});

    int counter = 0;
    while (!pq.empty()) {
        int currentIndex = pq.top().second;
        pq.pop();

        if (currentIndex == endingIndex)
            break;

        visited[currentIndex] = true;
        visitedCounter++;

        // for DFS this vector ought to be shuffled
        std::vector<int> neighbours = getNeighbours(currentIndex, visited);
        for (int neighbourIdx : neighbours) {
            prev[neighbourIdx] = currentIndex;
            distToStart[neighbourIdx] = distToStart[currentIndex] + 1;
            pq.push({dist[neighbourIdx] + distToStart[neighbourIdx], neighbourIdx});
        }
    }

    int last = endingIndex;

    do {
        last = prev[last];
        pathSize++;
    } while (last != startingIndex);

    std::cout << "visited: " << visitedCounter + 1<< std::endl;
    std::cout << "path size: " << pathSize << std::endl;

}
