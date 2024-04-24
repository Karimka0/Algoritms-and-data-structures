#include <algorithm>
#include <iostream>
#include <vector>
int cycle_st;
int cycle_end;

bool Dfs(std::vector<std::vector<int>>& graph, std::vector<int>& prev, std::vector<int>& colors, int top) {
    colors[top] = 1;
    for (size_t i = 0; i < graph[top].size(); ++i) {
        if (colors[graph[top][i]] == 0) {
            prev[graph[top][i]] = top;
            if (Dfs(graph, prev, colors, graph[top][i])) {
                return true;
            }
        } else if (colors[graph[top][i]] == 1) {
            cycle_st = graph[top][i];
            cycle_end = top;
            return true;
        }
    }
    colors[top] = 2;
    return false;
}

int main() {
    int points;
    int roads;
    std::cin >> points >> roads;
    std::vector<std::vector<int>> graph(points, std::vector<int>());
    std::vector<int> prev(points, -1);
    for (int i = 0; i < roads; ++i) {
        int top1;
        int top2;
        std::cin >> top1 >> top2;
        graph[top1 - 1].push_back(top2 - 1);
    }
    std::vector<int> colors(points, 0);
    cycle_st = -1;
    std::string ans = "NO";
    for (int top = 0; top < points; ++top) {
        if (Dfs(graph, prev, colors, top)) {
            ans = "YES";
            break;
        }
    }
    std::cout << ans << std::endl;
    if (ans == "YES") {
        std::vector<int> cycle;
        for (int vv = cycle_end; vv != cycle_st; vv=prev[vv]) {
            cycle.push_back(vv);
        }
        std::reverse(cycle.begin(), cycle.end());
        cycle.push_back(cycle_st);
        for (size_t i = 0; i < cycle.size(); ++i) {
            std::cout << cycle[i] + 1 << " ";
        }
    }
}