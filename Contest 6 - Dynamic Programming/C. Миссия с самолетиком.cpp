#include <iostream>
#include <vector>

int main() {
    int cnt;
    int kk;
    std::cin >> cnt >> kk;
    std::vector<std::vector<int>> dp;
    std::vector<int> temp1(kk + 1, 1);
    dp.push_back(temp1);
    int ans_n = 0;
    for (int nn = 1; nn <= cnt; ++nn) {
        std::vector<int> temp(kk + 1, 1);
        for (int k = 1; k <= kk; ++k) {
            temp[k] = dp[nn - 1][k] + dp[nn - 1][k - 1];
        }
        dp.push_back(temp);
        if (temp[kk] >= cnt) {
            ans_n = nn;
            break;
        }
    }
    if (cnt > 1 && kk == 0) {
        std::cout << -1;
    } else if (cnt == 1) {
        std::cout << 0;
    } else {
        std::cout << ans_n;
    }
}