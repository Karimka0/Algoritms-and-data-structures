//#include <iostream>
//#include <stack>
//#include <vector>
//
//int main() {
//    int potions;
//    std::cin >> potions;
//    std::stack<std::vector<long long>> weights;
//    long long max_square = 0;
//    long long k_zero = -1;
//    weights.push(std::vector{k_zero, k_zero});
//    for (long long i = 0; i < potions; ++i) {
//        long long weight;
//        std::cin >> weight;
//        while (!weights.empty() && weights.top()[1] >= weight) {
//            long long height = weights.top()[1];
//            weights.pop();
//            max_square = std::max(max_square, height * (i - 1 - weights.top()[0]));
//        }
//
//        weights.push(std::vector{i, weight});
//    }
//    long long right = weights.top()[0];
//    while (weights.top()[0] != -1) {
//        long long height = weights.top()[1];
//        weights.pop();
//        max_square = std::max(max_square, height * (right - weights.top()[0]));
//    }
//    std::cout << max_square;
//}