#include <iostream>
#include <queue>

/*program zaraz po uruchomieniu oczekuje na dane wejściowe; w pierwszej linijce wyjścia podaje odpowiedź*/

void loadInput(int *&graph, int &size) {
    int numberOfPiggyBanks;
    std::cin >> numberOfPiggyBanks;
    size = numberOfPiggyBanks + 1;
    graph = new int[size];

    int piggyBankIndex;
    for (int i = 1; i < size; i++) {
        std::cin >> piggyBankIndex;
        graph[i] = piggyBankIndex;
    }
}

void topologicalSort(std::vector<int> &inDegree, int *graph, int size) {
    std::queue<int> doomersQueue;
    for (int i = 1; i < size; i++) {
        inDegree[graph[i]]++;
    }

    for (int i = 1; i < size; i++) {
        if (inDegree[i] == 0) 
            doomersQueue.push(i);
    }

    while (!doomersQueue.empty()) {
        int currentVertex = doomersQueue.front();
        doomersQueue.pop();
        inDegree[graph[currentVertex]]--;
        if (inDegree[graph[currentVertex]] == 0)
            doomersQueue.push(graph[currentVertex]);
    }
}

void countCycles(std::vector<int> &inDegree, int *graph, int size) {
    int cycleCount = 0;

    for (int i = 1; i < size; i++) {
        int cycleStartIdx;
        if (inDegree[i] == 1) {
            cycleStartIdx = i;
            int next = graph[cycleStartIdx];
            while (next != cycleStartIdx) {
                inDegree[next] = 0;
                next = graph[next];
            }
            cycleCount++;
        }
    }

    std::cout << cycleCount << std::endl;
}

int main() {
    int *graph;
    int size;
    loadInput(graph, size);
    std::vector<int> inDegree(size, 0);

    topologicalSort(inDegree, graph, size);

    for (int i=0; i<size; i++) {
        std::cout<<inDegree[i]<<" ";
    }
    std::cout<<std::endl;

    countCycles(inDegree, graph, size);

    delete[] graph;
    return 0;
}
