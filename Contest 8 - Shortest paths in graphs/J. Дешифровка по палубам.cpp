#include <iostream>
#include <vector>
#include <queue>

const long long cMax = 1000000;
const long long cINF = 1000000000000000000LL;

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
        for (const auto& next: graph[top]) {
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
    long long cnt;
    long long up;
    long long down;
    long long entry;
    long long exit;
    long long teleports;
    std::cin >> cnt >> up >> down >> entry >> exit >> teleports;
    std::vector<std::vector<std::pair<long long, long long>>> graph(cMax + teleports,
                                                                    std::vector<std::pair<long long, long long>>());
    graph[0].emplace_back(up, 1);
    graph[cMax - 1].emplace_back(down, cMax - 2);
    for (long long i = 1; i <= cMax - 2; ++i) {
        graph[i].emplace_back(down, i - 1);
        graph[i].emplace_back(up, i + 1);
    }
    for (long long i = 0; i < teleports; ++i) {
        long long k;
        std::cin >> k;
        for (long long j = 0; j < k; ++j) {
            long long ki;
            std::cin >> ki;
            graph[ki - 1].emplace_back(entry, cMax + i);
            graph[cMax + i].emplace_back(exit, ki - 1);
        }
    }
    std::vector<long long> dist = Dijkstra(graph, 0);
    std::cout << dist[cnt - 1];
}