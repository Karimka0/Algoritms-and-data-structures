#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    int cnt;
    std::cin >> cnt;
    const int kInf = 2147483647;
    std::vector<int> dp(cnt + 1, kInf);
    std::vector<int> pos(cnt, kInf);
    std::vector<int> prev(cnt, kInf);
    dp[0] = -kInf;
    int number;
    for (int i = 0; i < cnt; ++i) {
        std::cin >> number;
        int jj = int(lower_bound(dp.begin(), dp.end(), -number) - dp.begin());
        if (dp[jj - 1] <= -number && -number <= dp[jj]) {
            dp[jj] = -number;
            pos[jj] = i;
            prev[i] = pos[jj - 1];
        }
    }
    int answer = 0;
    for (int i = 1; i <= cnt; ++i) {
        if (dp[i] != kInf) {
            ++answer;
        }
    }
    std::cout << answer << "\n";
    std::vector<int> indexes;
    int now_pos = pos[answer];
    while (now_pos != kInf) {
        indexes.push_back(now_pos);
        now_pos = prev[now_pos];
    }
    for (size_t i = indexes.size(); i > 0; --i) {
        std::cout << indexes[i - 1] + 1 << "\n";
    }
}