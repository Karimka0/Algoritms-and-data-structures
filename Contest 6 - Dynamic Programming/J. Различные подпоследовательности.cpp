#include <iostream>
#include <vector>

int main() {
    const int kMod = 1000000007;
    const int kSz = 1000000;
    int nn;
    std::cin >> nn;
    std::vector<int> ends(kSz + 1, 0);
    std::vector<int> dp(nn + 1, 0);
    for (int i = 1; i <= nn; ++i) {
        int number;
        std::cin >> number;
        dp[i] = ((dp[i - 1] * 2 + 1 - ends[number]) % kMod + kMod) % kMod;
        ends[number] = (dp[i - 1] + 1) % kMod;
    }
    std::cout << dp[nn];
}