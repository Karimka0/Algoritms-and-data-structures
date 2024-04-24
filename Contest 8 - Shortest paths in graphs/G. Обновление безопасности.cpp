#include <iostream>
#include <vector>
#include <queue>

const int cINF = 1000000;

void Bfs(std::vector<std::vector<int>>& graph, std::vector<int>& dist, int start) {
    std::queue<int> queue;
    dist[start] = 0;
    queue.push(start);
    while (!queue.empty()) {
        int v = queue.front();
        queue.pop();
        for (int to: graph[v]) {
            if (dist[to] == cINF) {
                dist[to] = dist[v];
                queue.push(to);
            }
        }
    }
}

int main() {
    int vertexes;
    std::cin >> vertexes;
    std::vector<std::vector<int>> graph(vertexes, std::vector<int>());
    int weight;
    for (int i = 0; i < vertexes; ++i) {
        for (int j = 0; j < vertexes; ++j) {
            std::cin >> weight;
            if (weight == 1) {
                graph[i].push_back(j);
            }
        }
    }
    for (int i = 0; i < vertexes; ++i) {
        std::vector<int> dist(vertexes, cINF);
        Bfs(graph, dist, i);
        for (int j = 0; j < vertexes; ++j) {
            if (dist[j] == cINF) {
                std::cout << "0" << " ";
            } else {
                std::cout << "1" << " ";
            }
        }
        std::cout << std::endl;
    }
}