#include <algorithm>
#include <iostream>
#include <vector>

const int kMaxSize = 4 * 300000;
long long tree[kMaxSize];

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
    tree[top] += delta;
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
  int cnt;
  std::cin >> cnt;
  std::vector<std::pair<long long, long long>> matrix(cnt);
  std::vector<std::pair<long long, long long>> compress(cnt);
  for (int i = 0; i < cnt; ++i) {
    long long left;
    long long right;
    std::cin >> left >> right;
    compress[i] = {left, right};
  }

  std::sort(compress.begin(), compress.end());
  long long cmp = 1;
  for (int i = 0; i < cnt; ++i) {
    if (i > 0 && compress[i].first > compress[i - 1].first) {
      ++cmp;
    }
    matrix[i] = {compress[i].second, -cmp};
  }
  std::sort(matrix.begin(), matrix.end());
  long long answer = 0;
  long long equal = 0;
  for (int i = 0; i < cnt; ++i) {
    if (i > 0 && matrix[i] == matrix[i - 1]) {
      ++equal;
    } else if (equal != 0) {
      answer -= equal * (equal + 1) / 2;
      equal = 0;
    }
    answer += Sum(1, 1, cnt, -matrix[i].second, cnt);
    Update(1, 1, cnt, -matrix[i].second, 1);
  }
  if (equal != 0) {
    answer -= equal * (equal + 1) / 2;
  }
  std::cout << answer;
}