#include <bits/stdc++.h>

int UpdateDp(const std::vector<std::vector<char>>& graph, std::vector<int>& dp, size_t mask, int cnt) {
    for (int i = 0; i < cnt; ++i) {
        if (((mask >> i) & 1) == 1) {
            for (int j = i + 1; j < cnt; ++j) {
                if (((mask >> j) & 1) == 1 && graph[i][j] == 'Y') {
                    dp[mask] = std::max(dp[mask], dp[mask ^ (1 << i) ^ (1 << j)] + 2);
                }
            }
        }
    }

    return dp[mask];
}


int MaxPairs(const std::vector<std::vector<char>>& graph, int cnt) {
    std::vector<int> dp(1 << cnt, 0);
    for (size_t mask = 0; mask < (1 << cnt); ++mask) {
        int count = std::popcount(mask);
        if (count % 2 == 0) {
            UpdateDp(graph, dp, mask, cnt);
        } else {
            for (int i = 0; i < cnt; ++i) {
                if (((mask >> i) & 1) == 1) {
                    dp[mask] = std::max(dp[mask], dp[mask ^ (1 << i)]);
                }
            }
        }
    }
    return dp[(1 << cnt) - 1];
}

int main() {
    int cnt;
    std::cin >> cnt;
    std::vector<std::vector<char>> graph(cnt, std::vector<char>(cnt));
    for (int i = 0; i < cnt; ++i) {
        for (int j = 0; j < cnt; ++j) {
            std::cin >> graph[i][j];
        }
    }
    std::cout << MaxPairs(graph, cnt) << std::endl;
}