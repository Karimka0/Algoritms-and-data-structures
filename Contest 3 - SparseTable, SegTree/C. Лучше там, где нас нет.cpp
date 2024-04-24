#include <iostream>
#include <vector>
const int kMaxSize = 8 * 100000;
int tree[kMaxSize];
int answer = -1;

void Build(std::vector<int>& leaves, int top, int tl, int tr) {
  if (tl == tr) {
    tree[top] = leaves[tl];
  } else {
    int tm = (tl + tr) >> 1;
    Build(leaves, top * 2, tl, tm);
    Build(leaves, top * 2 + 1, tm + 1, tr);
    tree[top] = std::max(tree[top * 2], tree[top * 2 + 1]);
  }
}

void Search(int top, int tl, int tr, int left, int val) {
  if (tl == tr) {
    answer = tl;
    return;
  }
  int tm = (tl + tr) >> 1;
  if (tree[top] < val) {
    answer = -1;
    return;
  }
  if (tree[top * 2] >= val && tm >= left) {
    Search(2 * top, tl, tm, left, val);
  }
  if (tr >= left && tree[2 * top + 1] >= val && answer == -1) {
    Search(2 * top + 1, tm + 1, tr, left, val);
  }
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
    tree[top] = std::max(tree[top * 2], tree[top * 2 + 1]);
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  int num;
  int requests;
  std::cin >> num >> requests;
  std::vector<int> places(num + 1, 0);
  for (int i = 1; i <= num; ++i) {
    std::cin >> places[i];
  }
  Build(places, 1, 1, num);
  int command;
  int index;
  int value;
  for (int i = 0; i < requests; ++i) {
    std::cin >> command >> index >> value;
    if (command == 0) {
      Update(1, 1, num, index, value);
    } else {
      Search(1, 1, num, index, value);
      std::cout << answer << "\n";
      answer = -1;
    }
  }
}