#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

int main() {
    const int kAccuracy = 9;
    std::cout << std::setprecision(kAccuracy);
    std::cout << std::fixed;
    int number_of_mandrakes;
    std::cin >> number_of_mandrakes;
    std::vector<double> volumes;
    volumes.push_back(0);
    for (int i = 0; i < number_of_mandrakes; ++i) {
        double volume;
        std::cin >> volume;
        volumes.push_back(log(volume) + volumes[i]);
    }
    int requests;
    std::cin >> requests;
    for (int i = 0; i < requests; ++i) {
        int left;
        int right;
        std::cin >> left >> right;
        left++;
        right++;
        double degree =
                (volumes[right] - volumes[left - 1]) / double(right - left + 1);
        std::cout << exp(degree) << "\n";
    }
}
