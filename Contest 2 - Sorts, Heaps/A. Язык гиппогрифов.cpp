//#include <iostream>
//#include <stack>
//
//int main() {
//    std::string scream;
//    std::cin >> scream;
//    std::stack<char> brackets;
//    bool answer = true;
//    int const kBr1 = 41;
//    int const kBr2 = 93;
//    int const kBr3 = 125;
//    for (char bracket : scream) {
//        if (bracket == kBr1 || bracket == kBr2 || bracket == kBr3) {
//            if (brackets.empty() || abs(brackets.top() - bracket) > 2) {
//                answer = false;
//                break;
//            }
//            brackets.pop();
//            continue;
//        }
//        brackets.push(bracket);
//    }
//    if (!brackets.empty()) {
//        answer = false;
//    }
//    if (answer || scream.empty()) {
//        std::cout << "YES";
//    } else {
//        std::cout << "NO";
//    }
//}