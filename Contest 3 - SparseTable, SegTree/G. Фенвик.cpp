#include <iostream>
#include <vector>

int Sum(std::vector<std::vector<int>>& tree, int xx, int yy) {
  int result = 0;
  for (int i = xx; i >= 0; i = (i & (i + 1)) - 1) {
    for (int j = yy; j >= 0; j = (j & (j + 1)) - 1) {
      result += tree[i][j];
    }
  }
  return result;
}

void Change(std::vector<std::vector<int>>& tree, int number, int xx, int yy,
            int delta) {
  for (int i = xx; i < number; i = (i | (i + 1))) {
    for (int j = yy; j < number; j = (j | (j + 1))) {
      tree[i][j] += delta;
    }
  }
}

int main() {
  int number;
  int requests;
  std::cin >> number >> requests;
  std::vector<std::vector<int>> tree(number, std::vector<int>(number, 0));
  for (int i = 0; i < requests; ++i) {
    std::string request;
    std::cin >> request;
    if (request == "ADD") {
      int xx;
      int yy;
      std::cin >> xx >> yy;
      --xx;
      --yy;
      Change(tree, number, xx, yy, 1);
    } else {
      int xx1;
      int yy1;
      int xx2;
      int yy2;
      std::cin >> xx1 >> yy1 >> xx2 >> yy2;
      int x2 = std::max(--xx1, --xx2);
      int x1 = std::min(--xx1, --xx2);
      int y2 = std::max(--yy1, --yy2);
      int y1 = std::min(--yy1, --yy2);
      int result = Sum(tree, x2, y2) + Sum(tree, x1, y1);
      result -= Sum(tree, x2, y1) + Sum(tree, x1, y2);
      std::cout << result << "\n";
    }
  }
}