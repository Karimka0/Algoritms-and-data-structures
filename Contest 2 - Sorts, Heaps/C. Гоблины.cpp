//#include <deque>
//#include <iostream>
//#include <string>
//
//void Add(std::deque<int>& deq1, std::deque<int>& deq2, int number) {
//    if (deq1.size() > deq2.size()) {
//        deq2.push_back(number);
//    } else {
//        deq2.push_back(number);
//        deq1.push_back(deq2.front());
//        deq2.pop_front();
//    }
//}
//
//void Left(std::deque<int>& deq1, std::deque<int>& deq2) {
//    if (deq1.size() > deq2.size()) {
//        deq1.pop_front();
//    } else {
//        deq1.pop_front();
//        deq1.push_back(deq2.front());
//        deq2.pop_front();
//    }
//}
//
//void Vip(std::deque<int>& deq1, std::deque<int>& deq2, int number) {
//    if (deq1.size() > deq2.size()) {
//        deq2.push_front(number);
//    } else {
//        deq1.push_back(number);
//    }
//}
//
//int main() {
//    int requests;
//    std::cin >> requests;
//    std::deque<int> deq1;
//    std::deque<int> deq2;
//    for (int i = 0; i < requests; ++i) {
//        std::string type;
//        std::cin >> type;
//        int number;
//        if (type == "+") {
//            std::cin >> number;
//            Add(deq1, deq2, number);
//        } else if (type == "-") {
//            std::cout << deq1.front() << "\n";
//            Left(deq1, deq2);
//        } else if (type == "*") {
//            std::cin >> number;
//            Vip(deq1, deq2, number);
//        }
//    }
//}