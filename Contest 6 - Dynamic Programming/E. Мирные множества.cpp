#include <iostream>
#include <vector>

int main() {
    int cnt;
    std::cin >> cnt;
    std::vector<std::vector<int>> dp;
    dp.emplace_back(cnt + 1, 1);
    for (int i = 1; i <= cnt; ++i) {
        dp.emplace_back();
        for (int j = 0; j <= cnt; ++j) {
            dp[i].push_back(0);
        }
    }
    for (int i = 1; i <= cnt; ++i) {
        dp[i][0] = 0;
        for (int j = 1; j <= cnt; ++j) {
            dp[i][j] = dp[i][j - 1];
            if (i >= j) {
                dp[i][j] += dp[i - j][j / 2];
            }
        }
    }
    std::cout << dp[cnt][cnt];
}