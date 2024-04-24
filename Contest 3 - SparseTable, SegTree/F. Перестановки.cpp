#include <cmath>
#include <iostream>
#include <vector>

class MergeTree {
 public:
  std::vector<std::vector<int>> segment_tree;
  int size;
  std::vector<std::vector<std::pair<int, int>>> borders;
  std::vector<std::pair<int, int>> indexes;

  MergeTree(std::vector<int>& array) {
    size = 1 << int(ceil(log2(array.size())));
    segment_tree = std::vector<std::vector<int>>(2 * size);
    borders = std::vector<std::vector<std::pair<int, int>>>(2 * size);
    indexes = std::vector<std::pair<int, int>>(2 * size, {0, 0});

    for (int i = 0; i < size; ++i) {
      if (i >= static_cast<int>(array.size())) {
        segment_tree[i + size].push_back(0);
      } else {
        segment_tree[i + size].push_back(array[i]);
      }
    }

    Create(1, 0, size - 1);
  }

  void Create(int top, int left_border, int right_border) {
    indexes[top] = {left_border, right_border};
    if (top >= size) {
      return;
    }

    int middle = (left_border + right_border) >> 1;
    Create(2 * top, left_border, middle);
    Create(2 * top + 1, middle + 1, right_border);
    std::vector<int>& now_tree = segment_tree[top];
    std::vector<int>& left_tree = segment_tree[2 * top];
    std::vector<int>& right_tree = segment_tree[2 * top + 1];

    size_t left = 0;
    size_t right = 0;
    while (left < left_tree.size() || right < right_tree.size()) {
      borders[top].emplace_back(left, right);
      if (right == right_tree.size() ||
          (left != left_tree.size() && left_tree[left] <= right_tree[right])) {
        now_tree.push_back(left_tree[left]);
        ++left;
      } else {
        now_tree.push_back(right_tree[right]);
        ++right;
      }
    }

    borders[top].emplace_back(left, right);
  }

  int Get(int index, int left, int right, int left_val, int right_val) {
    if (indexes[index].second < left || indexes[index].first > right) {
      return 0;
    }
    if (indexes[index].first >= left && indexes[index].second <= right) {
      return right_val - left_val;
    }

    int sum = 0;
    sum += Get(2 * index, left, right, borders[index][left_val].first,
               borders[index][right_val].first);
    sum += Get(2 * index + 1, left, right, borders[index][left_val].second,
               borders[index][right_val].second);
    return sum;
  }

  int GetSum(int left, int right, int left_value, int right_value) {
    return Get(1, --left, --right, RightBinSearch(left_value),
               RightBinSearch(right_value) + 1);
  }

  int RightBinSearch(int val) {
    int left = 0;
    int right = size;
    while (right > left + 1) {
      int middle = (left + right) >> 1;
      if (val >= segment_tree[1][middle]) {
        left = middle;
      } else {
        right = middle;
      }
    }
    return left;
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
  int num;
  int requests;
  std::cin >> num >> requests;
  std::vector<int> array(num);

  for (int i = 0; i < num; ++i) {
    std::cin >> array[i];
  }
  MergeTree segment_tree(array);

  for (int i = 0; i < requests; ++i) {
    int left;
    int right;
    int left_val;
    int right_val;
    std::cin >> left >> right >> left_val >> right_val;
    std::cout << segment_tree.GetSum(left, right, left_val, right_val) << "\n";
  }
  return 0;
}