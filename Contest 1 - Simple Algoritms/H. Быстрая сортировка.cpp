#include <iostream>
#include <vector>

void QuickSort(std::vector<long long>& vec, int left, int right) {
    int ii = left;
    int jj = right;
    int pivot = vec[(ii + jj) / 2];
    while (ii <= jj) {
        while (vec[ii] < pivot) {
            ii++;
        }
        while (vec[jj] > pivot) {
            jj--;
        }
        if (ii <= jj) {
            std::swap(vec[ii], vec[jj]);
            ii++;
            jj--;
        }
    }
    if (jj > left) {
        QuickSort(vec, left, jj);
    }
    if (ii < right) {
        QuickSort(vec, ii, right);
    }
}

int main() {
    int cnt;
    std::cin >> cnt;
    std::vector<long long> numbers;
    for (int i = 0; i < cnt; ++i) {
        long long num;
        std::cin >> num;
        numbers.push_back(num);
    }
    QuickSort(numbers, 0, cnt - 1);
    for (int i = 0; i < cnt; ++i) {
        std::cout << numbers[i] << " ";
    }
}