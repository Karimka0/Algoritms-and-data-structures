#include <deque>
#include <iostream>
#include <vector>

void Helper(long long number, std::deque<long long>& deq) {
  while (!deq.empty() && number < deq.back()) {
    deq.pop_back();
  }
  deq.push_back(number);
}

void Deleter(std::deque<long long>& deq1, std::deque<long long>& deq2) {
  if (deq2.front() == deq1.front()) {
    deq2.pop_front();
  }
  deq1.pop_front();
}

int main() {
  unsigned long long side;
  unsigned long long subside;
  std::cin >> side >> subside;
  std::vector<std::vector<long long>> mins;
  long long number;
  for (unsigned long long i = 0; i < side; i++) {
    std::vector<long long> min_now;
    std::deque<long long> substr;
    std::deque<long long> substr_mins;
    for (unsigned long long j = 0; j < side; j++) {
      std::cin >> number;
      if (substr.size() == subside - 1) {
        substr.push_back(number);
        Helper(number, substr_mins);
        min_now.push_back(substr_mins.front());
        Deleter(substr, substr_mins);
      } else {
        substr.push_back(number);
        Helper(number, substr_mins);
      }
    }
    mins.push_back(min_now);
  }

  std::vector<std::vector<long long>> minc;
  for (unsigned long long i = 0; i < side - subside + 1; i++) {
    std::vector<long long> min_now;
    minc.push_back(min_now);
  }

  for (unsigned long long i = 0; i < side - subside + 1; i++) {
    std::deque<long long> substr;
    std::deque<long long> substr_mins;
    for (unsigned long long j = 0; j < side; j++) {
      number = mins[j][i];
      if (substr.size() == subside - 1) {
        substr.push_back(number);
        Helper(number, substr_mins);
        minc[j - subside + 1].push_back(substr_mins.front());
        Deleter(substr, substr_mins);
      } else {
        substr.push_back(number);
        Helper(number, substr_mins);
      }
    }
  }
  for (unsigned long long i = 0; i < side - subside + 1; i++) {
    for (unsigned long long j = 0; j < side - subside + 1; j++) {
      std::cout << minc[i][j] << " ";
    }
    std::cout << "\n";
  }
}