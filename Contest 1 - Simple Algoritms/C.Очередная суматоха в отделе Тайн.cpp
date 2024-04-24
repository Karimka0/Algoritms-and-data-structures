#include <algorithm>
#include <iostream>
#include <vector>

int BinSearch(const std::vector<int>& vec1, const std::vector<int>& vec2,
              int size) {
    int left = 0;
    int right = size - 1;
    while (right - left >= 1) {
        int middle = (left + right) / 2;
        if (vec1[middle] > vec2[middle]) {
            right = middle;
        } else {
            left = middle + 1;
        }
    }
    return left;
}

int main() {
    int shelves_in_a;
    int shelves_in_b;
    int elements;
    std::cin >> shelves_in_a >> shelves_in_b >> elements;
    std::vector<std::vector<int>> rack_a;
    std::vector<std::vector<int>> rack_b;
    for (int i = 0; i < shelves_in_a; ++i) {
        std::vector<int> shelve;
        for (int j = 0; j < elements; ++j) {
            int book;
            std::cin >> book;
            shelve.push_back(book);
        }
        rack_a.push_back(shelve);
    }
    for (int i = 0; i < shelves_in_b; ++i) {
        std::vector<int> shelve;
        for (int j = 0; j < elements; ++j) {
            int book;
            std::cin >> book;
            shelve.push_back(book);
        }
        rack_b.push_back(shelve);
    }
    int requests;
    std::cin >> requests;
    for (int i = 0; i < requests; i++) {
        int ai;
        int bj;
        std::cin >> ai >> bj;
        int kk = BinSearch(rack_a[ai - 1], rack_b[bj - 1], elements);
        if (kk > 0 &&
            std::max(rack_a[ai - 1][kk], rack_b[bj - 1][kk]) >
            std::max(rack_a[ai - 1][kk - 1], rack_b[bj - 1][kk - 1])) {
            std::cout << kk << "\n";
        } else {
            std::cout << kk + 1 << "\n";
        }
    }
}