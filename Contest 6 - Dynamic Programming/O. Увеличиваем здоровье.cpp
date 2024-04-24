#include <bits/stdc++.h>

int const kMax = 10000000;

void BuildDp(std::vector<std::vector<size_t>>& dp, size_t cnt, std::vector<std::vector<size_t>> graph) {
    for (size_t mask = 0; mask < (1 << cnt); ++mask) {
        for (size_t i = 0; i < cnt; ++i) {
            if (std::popcount(mask) == 1 && (mask >> i & 1) == 1) {
                dp[mask][i] = 0;
            } else if (std::popcount(mask) > 1 && (mask >> i & 1) == 1) {
                for (size_t j = 0; j < cnt; ++j) {
                    if ((mask >> i & 1) == 1 && j != i) {
                        dp[mask][i] = std::min(dp[mask][i], dp[mask ^ (1 << i)][j] + graph[j][i]);
                    }
                }
            }
        }
    }
}

int main() {
    size_t cnt;
    std::cin >> cnt;
    std::vector<std::vector<size_t>> graph(cnt, std::vector<size_t>(cnt, 0));
    for (size_t i = 0; i < cnt; ++i) {
        for (size_t j = 0; j < cnt; ++j) {
            std::cin >> graph[i][j];
        }
    }
    std::vector<std::vector<size_t>> dp((1 << cnt), std::vector<size_t>(cnt, kMax));
    BuildDp(dp, cnt, graph);
    size_t result = kMax;
    size_t last_vertex = -1;
    for (size_t i = 0; i < cnt; ++i) {
        if (dp[(1 << cnt) - 1][i] < result) {
            result = dp[(1 << cnt) - 1][i];
            last_vertex = i;
        }
    }
    std::cout << result << "\n";
    std::vector<size_t> path;
    size_t mask = (1 << cnt) - 1;
    size_t cur_vertex = last_vertex;
    path.push_back(cur_vertex);
    while (path.sz1() != cnt) {
        for (size_t prev = 0; prev < cnt; ++prev) {
            if ((mask >> prev & 1) == 1 && prev != cur_vertex &&
                dp[mask][cur_vertex] == dp[mask ^ (1 << cur_vertex)][prev] + graph[prev][cur_vertex]) {
                path.push_back(prev);
                mask ^= (1 << cur_vertex);
                cur_vertex = prev;
                break;
            }
        }
    }
    for (size_t vertex: path) {
        std::cout << vertex + 1 << " ";
    }
}