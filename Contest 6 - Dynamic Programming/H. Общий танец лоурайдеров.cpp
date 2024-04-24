#include <iostream>
#include <vector>

int main() {
  std::string cj;
  std::string caesar;
  std::cin >> cj >> caesar;
  std::vector<std::vector<int>> dp;
  std::vector<std::vector<int>> prev;
  for (size_t i = 0; i <= cj.size(); ++i) {
    dp.emplace_back();
    for (size_t j = 0; j <= caesar.size(); ++j) {
      dp[i].push_back(0);
    }
  }
  for (size_t i = 0; i < cj.size(); ++i) {
    prev.emplace_back();
    for (size_t j = 0; j < caesar.size(); ++j) {
      prev[i].push_back(0);
    }
  }
  for (size_t i = 1; i <= cj.size(); ++i) {
    for (size_t j = 1; j <= caesar.size(); ++j) {
      if (cj[i - 1] == caesar[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1] + 1;
        prev[i - 1][j - 1] = 0;
      } else if (dp[i - 1][j] >= dp[i][j - 1]) {
        dp[i][j] = dp[i - 1][j];
        prev[i - 1][j - 1] = 1;
      } else {
        dp[i][j] = dp[i][j - 1];
        prev[i - 1][j - 1] = 2;
      }
    }
  }
  std::vector<size_t> ans1;
  std::vector<size_t> ans2;
  size_t i1 = cj.size();
  size_t i2 = caesar.size();
  while (dp[i1][i2] > 0 && i1 != 0 && i2 != 0) {
    if (prev[i1 - 1][i2 - 1] == 0) {
      ans1.push_back(i1);
      ans2.push_back(i2);
      --i1;
      --i2;
    } else if (prev[i1 - 1][i2 - 1] == 1) {
      --i1;
    } else {
      --i2;
    }
  }
  std::cout << dp[cj.size()][caesar.size()] << "\n";
  for (size_t i = ans1.size(); i != 0; --i) {
    std::cout << ans1[i - 1] << " ";
  }
  std::cout << "\n";
  for (size_t i = ans2.size(); i != 0; --i) {
    std::cout << ans2[i - 1] << " ";
  }
}