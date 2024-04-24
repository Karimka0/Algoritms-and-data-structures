#include <iostream>
#include <vector>

bool Can(int p1, int p2, int nn) {
    for (int i = 0; i < nn - 1; ++i) {
        int b1 = (p1 >> i) & 1;
        int b2 = (p1 >> (i + 1)) & 1;
        int b3 = (p2 >> i) & 1;
        int b4 = (p2 >> (i + 1)) & 1;
        if (b1 == 1 && b2 == 1 && b3 == 1 && b4 == 1) {
            return false;
        }
        if (b1 == 0 && b2 == 0 && b3 == 0 && b4 == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    size_t nn;
    size_t mm;
    std::cin >> nn >> mm;
    if (mm < nn) {
        size_t temp = nn;
        nn = mm;
        mm = temp;
    }
    std::vector<std::vector<int>> dp((1 << nn), std::vector<int>((1 << nn), 0));
    std::vector<std::vector<int>> ap(mm, std::vector<int>((1 << nn), 0));
    for (int i = 0; i < (1 << nn); ++i) {
        for (int j = 0; j < (1 << nn); ++j) {
            if (Can(i, j, nn)) {
                dp[i][j] = 1;
            } else {
                dp[i][j] = 0;
            }
        }
    }
    for (int i = 0; i < (1 << nn); ++i) {
        ap[0][i] = 1;
    }
    for (size_t k = 1; k < mm; ++k) {
        for (int i = 0; i < (1 << nn); ++i) {
            for (int j = 0; j < (1 << nn); ++j) {
                ap[k][i] = ap[k][i] + ap[k - 1][j] * dp[j][i];
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < (1 << nn); ++i) {
        ans += ap[mm - 1][i];
    }
    std::cout << ans;
}
