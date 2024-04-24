#include <iostream>
#include <vector>

int main() {
  int cnt;
  int capacity;
  std::cin >> cnt >> capacity;
  std::vector<int> resources(cnt + 1, 0);
  std::vector<int> awards(cnt + 1, 0);
  for (int i = 1; i <= cnt; ++i) {
    std::cin >> resources[i];
  }
  for (int i = 1; i <= cnt; ++i) {
    std::cin >> awards[i];
  }
  std::vector<std::vector<int>> dp(cnt + 1, std::vector<int>(capacity + 1, 0));
  for (int i = 1; i <= cnt; ++i) {
    for (int j = 1; j <= capacity; ++j) {
      if (j >= resources[i]) {
        dp[i][j] =
            std::max(dp[i - 1][j], dp[i - 1][j - resources[i]] + awards[i]);
      } else {
        dp[i][j] = dp[i - 1][j];
      }
    }
  }
  std::vector<int> answer;
  int ii = cnt;
  int jj = capacity;
  while (dp[ii][jj] > 0) {
    if (dp[ii - 1][jj] == dp[ii][jj]) {
      --ii;
    } else {
      answer.push_back(ii);
      jj -= resources[ii];
      --ii;
    }
  }
  for (size_t i = answer.size(); i > 0; --i) {
    std::cout << answer[i - 1] << "\n";
  }
}