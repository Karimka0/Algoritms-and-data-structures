#include <iostream>
#include <vector>

const int cINF = 30000;
struct Edge {
    int from;
    int to;
    int weight;
};

void FordBellman(std::vector<Edge>& graph, int vertexes, int start) {
    std::vector<int> dp(vertexes, cINF);
    dp[start] = 0;
    for (int i = 0; i < vertexes - 1; ++i) {
        for (auto edge: graph) {
            if (dp[edge.from] < cINF) {
                dp[edge.to] = std::min(dp[edge.to], dp[edge.from] + edge.weight);
            }
        }
    }
    for (int i = 0; i < vertexes; ++i) {
        std::cout << dp[i] << " ";
    }
}

int main() {
    int vertexes;
    int edges;
    std::cin >> vertexes >> edges;
    std::vector<Edge> graph(edges);
    for (int j = 0; j < edges; ++j) {
        int v1;
        int v2;
        int weight;
        std::cin >> v1 >> v2 >> weight;
        graph.emplace_back(v1 - 1, v2 -1, weight);
    }
    FordBellman(graph, vertexes, 0);
}