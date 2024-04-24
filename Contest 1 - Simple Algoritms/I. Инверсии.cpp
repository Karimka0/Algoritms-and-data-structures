#include <algorithm>
#include <iostream>
#include <vector>

int Merge(std::vector<long long>& vec, int left, int middle, int right) {
    std::vector<long long> temp;
    int ii = left;
    int jj = middle + 1;
    int inversions = 0;
    while (ii <= middle || jj <= right) {
        if (ii <= middle && jj <= right && vec[ii] > vec[jj]) {
            inversions += middle + 1 - ii;
        }
        if (jj > right || (ii <= middle && vec[ii] < vec[jj])) {
            temp.push_back(vec[ii]);
            ++ii;
        } else {
            temp.push_back(vec[jj]);
            ++jj;
        }
    }
    for (int i = left; i <= right; ++i) {
        vec[i] = temp[i - left];
    }
    return inversions;
}

int MergeSort(std::vector<long long>& vec, int left, int right) {
    if (left < right) {
        int middle = (right + left) / 2;
        int inversions = 0;
        inversions += MergeSort(vec, left, middle);
        inversions += MergeSort(vec, middle + 1, right);
        inversions += Merge(vec, left, middle, right);
        return inversions;
    }
    return 0;
}

int main() {
    int num;
    std::cin >> num;
    std::vector<long long> numbers;
    for (int i = 0; i < num; i++) {
        long long number;
        std::cin >> number;
        numbers.push_back(number);
    }
    std::cout << MergeSort(numbers, 0, num - 1) << "\n";
}