#include <iomanip>
#include <iostream>
#include <vector>

void Update(std::vector<int>& tree, int top, int left, int right,
            std::pair<int, int> storage) {
  tree[top] += storage.second;
  if (left == right) {
    return;
  }
  int middle = (left + right) / 2;
  if (storage.first <= middle) {
    Update(tree, top * 2, left, middle, storage);
  } else {
    Update(tree, top * 2 + 1, middle + 1, right, storage);
  }
}

int GetSum(std::vector<int>& tree, int top, std::pair<int, int> borders,
           int req_left, int req_right) {
  if (req_left == borders.first && req_right == borders.second) {
    return tree[top];
  }
  if (tree[top] == 0) {
    return 0;
  }
  int ans = 0;
  int middle = (borders.first + borders.second) / 2;
  int right = borders.second;
  if (req_left <= middle) {
    borders.second = middle;
    ans +=
        GetSum(tree, 2 * top, borders, req_left, std::min(middle, req_right));
  }
  if (req_right >= middle + 1) {
    borders.first = middle + 1;
    borders.second = right;
    ans += GetSum(tree, 2 * top + 1, borders, std::max(req_left, middle + 1),
                  req_right);
  }
  return ans;
}

int main() {
  const int kAccuracy = 7;
  std::setprecision(kAccuracy);
  const int kAmount = 42195;
  std::vector<int> tree(kAmount * 4, 0);
  const int kAmount2 = 100001;
  std::vector<int> rappers(kAmount2, 0);
  int requests;
  std::cin >> requests;
  std::string command;
  std::pair<int, int> storage;
  std::pair<int, int> borders(1, kAmount);

  int user;
  for (int i = 0; i < requests; i++) {
    std::cin >> command;
    if (command == "RUN") {
      int page;
      std::cin >> user >> page;
      if (rappers[user] != 0) {
        storage.first = rappers[user];
        storage.second = -1;
        Update(tree, 1, 1, kAmount, storage);
      }
      storage.first = page;
      storage.second = 1;
      Update(tree, 1, 1, kAmount, storage);
      rappers[user] = page;

    } else if (command == "CHEER") {
      std::cin >> user;
      if (rappers[user] == 0) {
        std::cout << 0 << "\n";
      } else if (tree[1] == 1) {
        std::cout << 1 << "\n";
      } else {
        std::cout << static_cast<double>(
                         GetSum(tree, 1, borders, 1, rappers[user] - 1)) /
                         (tree[1] - 1)
                  << "\n";
      }
    }
  }
}