#include <iostream>
#include <vector>

int Partition(std::vector<int>& arr, int left, int right) {
    int pivot = arr[right];
    int ii = left;
    for (int jj = left; jj <= right - 1; jj++) {
        if (arr[jj] <= pivot) {
            std::swap(arr[ii], arr[jj]);
            ii++;
        }
    }
    std::swap(arr[ii], arr[right]);
    return ii;
}

int QuickSelect(std::vector<int>& arr, int left, int right, int kk) {
    if (kk > 0 && kk <= right - left + 1) {
        int index = Partition(arr, left, right);
        if (index - left == kk - 1) {
            return arr[index];
        }
        if (index - left > kk - 1) {
            return QuickSelect(arr, left, index - 1, kk);
        }
        return QuickSelect(arr, index + 1, right, kk - index + left - 1);
    }
    return 0;
}

int main() {
    int number;
    int kk;
    int a0;
    int a1;
    std::cin >> number >> kk >> a0 >> a1;
    std::vector<int> numbers;
    numbers.push_back(a0);
    numbers.push_back(a1);
    const int kDiv = 10004321;
    const int kInd1 = 123;
    const int kInd2 = 45;
    for (int i = 2; i < number; ++i) {
        numbers.push_back((kInd1 * numbers[i - 1] + kInd2 * numbers[i - 2]) % kDiv);
    }
    std::cout << QuickSelect(numbers, 0, number - 1, kk);
}