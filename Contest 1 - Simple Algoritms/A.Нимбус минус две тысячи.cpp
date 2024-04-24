#include <iostream>
#include <vector>

int main() {
    int number_of_candidates;
    std::cin >> number_of_candidates;
    std::vector<long long> speeds;
    for (int i = 0; i < number_of_candidates; i++) {
        long long candidate;
        std::cin >> candidate;
        speeds.push_back(candidate);
    }
    std::vector<long long> prefixes_min;
    std::vector<long long> suffixes_min;
    prefixes_min.push_back(speeds[0]);
    for (int i = 1; i < number_of_candidates; ++i) {
        prefixes_min.push_back(std::min(prefixes_min[i - 1], speeds[i]));
    }
    suffixes_min.push_back(speeds[number_of_candidates - 1]);
    for (int j = 1; j < number_of_candidates; ++j) {
        suffixes_min.push_back(
                std::min(suffixes_min[j - 1], speeds[number_of_candidates - j - 1]));
    }
    int requests;
    std::cin >> requests;
    for (int i = 0; i < requests; ++i) {
        int left;
        int right;
        std::cin >> left >> right;
        std::cout << std::min(prefixes_min[left - 1],
                              suffixes_min[number_of_candidates - right])
                  << "\n";
    }
}
