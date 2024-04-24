#include <iostream>
#include <vector>

int main() {
    int nn;
    int mm;
    std::cin >> nn >> mm;
    std::vector<int> cj(nn);
    std::vector<int> dj(mm);
    for (int i = 0; i < nn; ++i) {
        std::cin >> cj[i];
    }
    for (int i = 0; i < mm; ++i) {
        std::cin >> dj[i];
    }

    std::vector<std::vector<int>> dp;
    for (int i = 0; i <= nn; ++i) {
        dp.emplace_back();
        for (int j = 0; j <= mm; ++j) {
            dp[i].push_back(0);
        }
    }

    for (int i = 1; i <= nn; ++i) {
        int best = 0;
        for (int j = 1; j <= mm; ++j) {
            dp[i][j] = dp[i - 1][j];
            if (cj[i - 1] == dj[j - 1] && dp[i - 1][j] < best + 1) {
                dp[i][j] = best + 1;
            }
            if (cj[i - 1] > dj[j - 1] && dp[i - 1][j] > best) {
                best = dp[i - 1][j];
            }
        }
    }
    int ans = 0;
    for (int i = 1; i <= mm; ++i) {
        ans = std::max(ans, dp[nn][i]);
    }
    std::cout << ans;
}