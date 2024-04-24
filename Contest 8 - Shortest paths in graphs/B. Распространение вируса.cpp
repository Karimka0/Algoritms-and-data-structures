#include <iostream>
#include <vector>
#include <queue>

const long long cINF = 9223372036854775806;

std::vector<long long> Dijkstra(std::vector<std::vector<std::pair<long long, long long>>>& graph, long long start) {
    std::priority_queue<std::pair<long long, long long>, std::vector<std::pair<long long, long long>>, std::greater<>> heap;
    std::vector<long long> dist(graph.size(), cINF);
    dist[start] = 0;
    heap.emplace(0, start);
    while (!heap.empty()) {
        long long now_dist = heap.top().first;
        long long top = heap.top().second;
        heap.pop();
        if (now_dist > dist[top]) {
            continue;
        }
        for (const auto &next: graph[top]) {
            long long v = next.second;
            long long weight = next.first;
            if (dist[v] > dist[top] + weight) {
                dist[v] = dist[top] + weight;
                heap.emplace(dist[v], v);
            }
        }
    }
    return dist;
}

int main() {
    long long vertexes;
    long long edges;
    long long viruses;
    std::cin >> vertexes >> edges >> viruses;
    std::vector<long long> infected(viruses);
    for (long long i = 0; i < viruses; ++i) {
        std::cin >> infected[i];
    }
    
    std::vector<std::vector<std::pair<long long, long long>>> graph(vertexes);
    for (long long j = 0; j < edges; ++j) {
        long long v1;
        long long v2;
        long long weight;
        std::cin >> v1 >> v2 >> weight;
        graph[v1 - 1].emplace_back(weight, v2 - 1);
        graph[v2 - 1].emplace_back(weight, v1 - 1);
    }
    long long start;
    long long medicine;
    std::cin >> start >> medicine;
    std::vector<long long> dist = Dijkstra(graph, medicine - 1);
    long long answer = dist[start - 1];
    for (long long i = 0; i < viruses; ++i) {
        if (dist[infected[i] - 1] <= answer) {
            answer = -1;
            break;
        }
    }
    if (answer == cINF) {
        answer = -1;
    }
    std::cout << answer;
}