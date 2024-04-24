#include <iostream>
#include <vector>

unsigned long long Pow(unsigned long long base, int deg) {
    unsigned long long result = 1;
    for (int i = 0; i < deg; ++i) {
        result *= base;
    }
    return result;
}

void BitwiseSort(std::vector<unsigned long long>& vector, int cnt, int digit) {
    std::vector<std::vector<unsigned long long>> temp;
    const int kBase = 10;
    for (int i = 0; i < kBase; ++i) {
        std::vector<unsigned long long> now_temp;
        temp.push_back(now_temp);
    }
    unsigned long long disch = Pow(kBase, digit - 1);
    for (int i = 0; i < cnt; ++i) {
        temp[(vector[i] / disch) % kBase].push_back(vector[i]);
    }
    vector.clear();
    for (int i = 0; i < kBase; ++i) {
        for (unsigned long long jj : temp[i]) {
            vector.push_back(jj);
        }
    }
}

int main() {
    int cnt;
    std::cin >> cnt;
    std::vector<unsigned long long> numbers;
    for (int i = 0; i < cnt; ++i) {
        unsigned long long number;
        std::cin >> number;
        numbers.push_back(number);
    }
    const int kBase = 20;
    for (int i = 1; i <= kBase; ++i) {
        BitwiseSort(numbers, cnt, i);
    }
    for (int i = 0; i < cnt; ++i) {
        std::cout << numbers[i] << "\n";
    }
}
