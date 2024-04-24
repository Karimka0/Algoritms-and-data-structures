#include <algorithm>
#include <iostream>
#include <vector>

std::vector<int> answer;

bool Dfs(std::vector<std::vector<int>>& graph, std::vector<int>& colors, int top) {
    colors[top] = 1;
    for (size_t i = 0; i < graph[top].size(); ++i) {
        if (colors[graph[top][i]] == 0) {
            if (Dfs(graph, colors, graph[top][i])) {
                return true;
            }
        } else if (colors[graph[top][i]] == 1) {
            return true;
        }
    }
    colors[top] = 2;
    answer.push_back(top);
    return false;
}

int main() {
    int vertices;
    int edges;
    std::cin >> vertices >> edges;
    std::vector<std::vector<int>> graph(vertices, std::vector<int>());
    std::vector<int> colors(vertices, 0);
    for (int i = 0; i < edges; ++i) {
        int top1;
        int top2;
        std::cin >> top1 >> top2;
        graph[top1 - 1].push_back(top2 - 1);
    }
    bool can = true;
    for (int top = 0; top < vertices; ++top) {
        if (colors[top] == 0) {
            if (Dfs(graph, colors, top)) {
                can = false;
            }
        }
    }
    if (!can) {
        std::cout << -1;
    } else {
        std::reverse(answer.begin(), answer.end());
        for (int top: answer) {
            std::cout << top + 1 << " ";
        }
    }
}