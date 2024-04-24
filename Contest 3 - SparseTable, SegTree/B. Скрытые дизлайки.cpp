#include <iostream>
#include <vector>

const int kMaxSize = 4 * 100000;
int tree[kMaxSize];

void Build(std::vector<int>& leaves, int top, int tl, int tr) {
  if (tl == tr) {
    tree[top] = leaves[tl];
  } else {
    int tm = (tl + tr) >> 1;
    Build(leaves, top * 2, tl, tm);
    Build(leaves, top * 2 + 1, tm + 1, tr);
    tree[top] = tree[top * 2] + tree[top * 2 + 1];
  }
}

int Sum(int top, int tl, int tr, int left, int right) {
  if (left > right) {
    return 0;
  }
  if (left == tl && right == tr) {
    return tree[top];
  }
  int tm = (tl + tr) >> 1;
  return Sum(top * 2, tl, tm, left, std::min(right, tm)) +
         Sum(top * 2 + 1, tm + 1, tr, std::max(left, tm + 1), right);
}

void Update(int top, int tl, int tr, int pos, int delta) {
  if (tl == tr) {
    tree[top] = delta;
  } else {
    int tm = (tl + tr) >> 1;
    if (pos <= tm) {
      Update(top * 2, tl, tm, pos, delta);
    } else {
      Update(top * 2 + 1, tm + 1, tr, pos, delta);
    }
    tree[top] = tree[top * 2] + tree[top * 2 + 1];
  }
}

int main() {
  int num;
  std::cin >> num;
  std::vector<int> reactions(num + 1, 0);
  for (int i = 1; i <= num; ++i) {
    int number;
    std::cin >> number;
    if (i % 2 == 1) {
      reactions[i] = number;
    } else {
      reactions[i] = -number;
    }
  }
  Build(reactions, 1, 1, num);
  int requests;
  std::cin >> requests;
  int command;
  for (int k = 0; k < requests; ++k) {
    std::cin >> command;
    if (command == 0) {
      int ii;
      int jj;
      std::cin >> ii >> jj;
      if (ii % 2 == 1) {
        Update(1, 1, num, ii, jj);
      } else {
        Update(1, 1, num, ii, -jj);
      }
    } else {
      int left;
      int right;
      std::cin >> left >> right;
      if (left % 2 == 1) {
        std::cout << Sum(1, 1, num, left, right) << "\n";
      } else {
        std::cout << -Sum(1, 1, num, left, right) << "\n";
      }
    }
  }
}