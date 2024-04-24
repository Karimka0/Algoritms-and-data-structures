#include <iostream>
#include <vector>

const size_t kMod = 1000000007;
const char kPlus = 43;
const char kMinus = 45;

std::vector<std::vector<int>> Transpose(std::vector<std::vector<int>>& city, int& nn, int& mm) {
    if (nn >= mm) {
        return city;
    }
    std::swap(nn, mm);
    std::vector<std::vector<int>> result(nn, std::vector<int>(mm, 0));
    for (int i = 0; i < nn; ++i) {
        for (int j = 0; j < mm; ++j) {
            result[i][j] = city[j][i];
        }
    }
    return result;
}

bool Can(size_t mask, size_t index, std::vector<std::vector<int>>& city) {
    size_t deg = 1;
    for (size_t ii: city[index]) {
        if (((mask & deg) == 0 && ii == 1) || ((mask & deg) != 0 && ii == 2)) {
            return false;
        }
        deg <<= 1;
    }
    return true;
}

std::pair<size_t, bool> Mask(size_t mask, size_t new_mask, std::vector<std::vector<int>>& city,
                             size_t index) {
    size_t deg = 1;
    size_t last_bit = new_mask;
    size_t marked_bit = static_cast<size_t>((mask & 1) != 0);
    bool fit = true;
    for (size_t i = 1; i < city[0].size(); ++i) {
        deg <<= 1;
        size_t now_bit = static_cast<size_t>((mask & deg) != 0);
        size_t now_sum = now_bit + marked_bit + last_bit;
        if (now_sum == 3 || now_sum == 0 || (city[index][i] != 0 && now_sum != static_cast<size_t>(city[index][i]))) {
            fit = false;
            break;
        }
        if (now_sum == 1) {
            new_mask += deg;
        }
        last_bit = static_cast<size_t>((now_sum == 1));
        marked_bit = now_bit;
    }
    return {new_mask, fit};
}

void Counting(std::vector<std::vector<int>>& city, std::vector<std::vector<size_t>>& res, size_t nn, size_t mm) {
    for (size_t i = 1; i < nn; ++i) {
        for (size_t j = 0; j < (1 << mm); ++j) {
            if (city[i - 1][0] != 1) {
                std::pair<size_t, bool> now = Mask(j, 0, city, i - 1);
                if (now.second) {
                    res[i][j] = res[i - 1][now.first];
                }
            }
            if (city[i - 1][0] != 2) {
                std::pair<size_t, bool> now = Mask(j, 1, city, i - 1);
                if (now.second) {
                    res[i][j] += res[i - 1][now.first];
                }
            }
            res[i][j] %= kMod;
        }
    }
}

int main() {
    int nn;
    int mm;
    std::cin >> nn >> mm;
    std::vector<std::vector<int>> city(nn,
                                       std::vector<int>(mm, 0));
    for (int i = 0; i < nn; ++i) {
        for (int j = 0; j < mm; ++j) {
            char type;
            std::cin >> type;
            if (type == kPlus) {
                city[i][j] = 1;
            } else if (type == kMinus) {
                city[i][j] = 2;
            }
        }
    }
    city = Transpose(city, nn, mm);
    std::vector<std::vector<size_t>> dp(
            nn, std::vector<size_t>((1 << mm), 0));
    dp[0] = std::vector<size_t>((1 << mm), 1);
    for (size_t i = 0; i < (1 << mm); ++i) {
        if (!Can(i, 0, city)) {
            dp[0][i] = 0;
        }
    }
    Counting(city, dp, nn, mm);
    size_t answer = 0;
    for (size_t i = 0; i < (1 << mm); ++i) {
        if (Can(i, nn - 1, city)) {
            answer += dp[nn - 1][i];
            answer %= kMod;
        }
    }
    std::cout << answer % kMod;
}