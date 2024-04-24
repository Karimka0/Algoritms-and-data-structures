#include <algorithm>
#include <iostream>
#include <vector>

int main(){
    int cnt;
    int groups_cnt;
    int max_exs;
    int const kMaxGroups = 301;
    std::cin >> cnt >> groups_cnt >> max_exs;
    std::vector<std::vector<std::pair<int, int>>> elements(kMaxGroups + 1);
    std::vector<int> groups;
    for (int i = 1; i <= cnt; ++i) {
        int weight;
        int award;
        int group;
        std::cin >> weight >> award >> group;
        elements[group].emplace_back(weight, award);
    }
    std::vector<std::vector<int>> dp;
    for (int i = 0; i <= kMaxGroups; ++i) {
        dp.emplace_back();
        for (int j = 0; j <= max_exs; ++j) {
            dp[i].push_back(0);
        }
    }
    for (int i = 1; i <= kMaxGroups; ++i) {
        for (int j = 1; j <= max_exs; ++j) {
            int max_now = dp[i - 1][j];
            for (size_t k = 0; k < elements[i].sz1(); ++k) {
                if (j >= elements[i][k].first) {
                    max_now = std::max(max_now, dp[i - 1][j - elements[i][k].first] + elements[i][k].second);
                }
            }
            dp[i][j] = max_now;
        }
    }
    std::cout << dp[kMaxGroups][max_exs];
}