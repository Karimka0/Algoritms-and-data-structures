#include <iostream>
#include <vector>
#include <queue>

const int cINF = 2009000999;

std::vector<int> Dijkstra(std::vector<std::vector<std::pair<int, int>>> &graph, int start) {
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> heap;
    std::vector<int> dist(graph.size(), cINF);
    dist[start] = 0;
    heap.emplace(0, start);
    while (!heap.empty()) {
        int now_dist = heap.top().first;
        int top = heap.top().second;
        heap.pop();
        if (now_dist > dist[top]) {
            continue;
        }
        for (const auto &next: graph[top]) {
            int v = next.second;
            int weight = next.first;
            if (dist[v] > dist[top] + weight) {
                dist[v] = dist[top] + weight;
                heap.emplace(dist[v], v);
            }
        }
    }
    return dist;
}

int main() {
    int requests;
    std::cin >> requests;
    for (int i = 0; i < requests; ++i) {
        int rooms;
        int edges;
        std::cin >> rooms >> edges;
        std::vector<std::vector<std::pair<int, int>>> graph(rooms);
        for (int j = 0; j < edges; ++j) {
            int v1;
            int v2;
            int weight;
            std::cin >> v1 >> v2 >> weight;
            graph[v1].emplace_back(weight, v2);
            graph[v2].emplace_back(weight, v1);
        }
        int start;
        std::cin >> start;
        std::vector<int> dist = Dijkstra(graph, start);
        for (auto d: dist) {
            std::cout << d << " ";
        }
        std::cout << "\n";
    }
}