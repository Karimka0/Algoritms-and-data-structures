#include <iostream>
#include <vector>


const int cNoEdge = 100000;
const int cINF = 1000000000;
struct Edge {
    int from;
    int to;
    int weight;
};

bool FordBellman(std::vector<Edge>& graph, std::vector<int>& cycle, int vertexes, int start) {
    std::vector<int> dp(vertexes, cINF);
    std::vector<int> prev(vertexes, -1);
    int check = -1;
    dp[start] = 0;
    for (int i = 0; i < vertexes; ++i) {
        check = -1;
        for (auto edge: graph) {
            if (dp[edge.from] < cNoEdge && dp[edge.from] + edge.weight < dp[edge.to]) {
                dp[edge.to] = std::max(-cINF, dp[edge.from] + edge.weight);
                prev[edge.to] = edge.from;
                check = edge.to;
            }
        }
    }
    if (check == -1) {
        return false;
    }
    int begin = check;
    for (int i = 0; i < vertexes; ++i) {
        begin = prev[begin];
    }
    for (int now = begin;; now = prev[now]) {
        cycle.push_back(now);
        if (now == begin && cycle.size() > 1) {
            break;
        }
    }
    return true;
}

int main() {
    int vertexes;
    std::cin >> vertexes;
    std::vector<Edge> graph;
    int weight;
    for (int i = 0; i < vertexes; ++i) {
        for (int j = 0; j < vertexes; ++j) {
            std::cin >> weight;
            if (weight < cNoEdge) {
                graph.push_back({i, j, weight});
            }
        }
    }
    std::vector<int> cycle;
    bool ans = false;
    for (int i = 0; i < vertexes; ++i) {
        ans = FordBellman(graph, cycle, vertexes, i);
        if (ans) {
            break;
        }
    }
    if (!ans) {
        std::cout << "NO";
    } else {
        std::cout << "YES" << "\n" << cycle.size() << "\n";
        for (size_t i = cycle.size(); i != 0; --i) {
            std::cout << cycle[i - 1] + 1 << " ";
        }
    }
}