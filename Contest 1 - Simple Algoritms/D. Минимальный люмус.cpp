#include <algorithm>
#include <iostream>
#include <vector>

long long Check(long long now_l, const std::vector<long long>& vec1) {
    long long section_now = vec1[0] + now_l;
    long long now_k = 0;
    for (long long ii : vec1) {
        if (section_now < ii) {
            now_k++;
            section_now = ii + now_l;
        }
    }
    now_k++;
    if (vec1[0] == vec1[vec1.size() - 1]) {
        now_k = 0;
    }
    return now_k;
}

int main() {
    int receivers;
    int spells;
    std::cin >> receivers >> spells;
    std::vector<long long> coordinates;
    for (int i = 0; i < receivers; ++i) {
        long long x;
        std::cin >> x;
        coordinates.push_back(x);
    }
    std::sort(coordinates.begin(), coordinates.end());
    const long long kMaxL = 2000000000;
    long long left = 0;
    long long right = kMaxL;
    while (right - left >= 1) {
        long long middle = (right + left) / 2;
        if (Check(middle, coordinates) > spells) {
            left = middle + 1;
        } else {
            right = middle;
        }
    }
    std::cout << left;
}