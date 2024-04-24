#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    int number_of_fragments;
    std::cin >> number_of_fragments;
    std::vector<std::vector<int>> fragments;
    for (int i = 0; i < number_of_fragments; ++i) {
        int left;
        int right;
        std::cin >> left >> right;
        std::vector<int> vec;
        vec.push_back(left);
        vec.push_back(right);
        fragments.push_back(vec);
    }
    std::sort(fragments.begin(), fragments.end());
    std::vector<int> answers;
    int answer = number_of_fragments;
    int left_now = fragments[0][0];
    int right_now = fragments[0][1];
    for (int i = 1; i < number_of_fragments; ++i) {
        if (fragments[i][0] <= right_now) {
            right_now = std::max(right_now, fragments[i][1]);
            --answer;
        } else {
            answers.push_back(left_now);
            answers.push_back(right_now);
            left_now = fragments[i][0];
            right_now = fragments[i][1];
        }
    }
    answers.push_back(left_now);
    answers.push_back(right_now);
    std::cout << answer << "\n";
    for (int i = 0; i < answer * 2; i += 2) {
        std::cout << answers[i] << " " << answers[i + 1] << "\n";
    }
}
