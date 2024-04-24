#include <algorithm>
#include <iostream>
#include <vector>

const int kMaxSize = 4 * 100000;
long long tree[kMaxSize];

long long Sum(long long top, long long tl, long long tr, long long left,
              long long right) {
  if (tree[top] == 0) {
    return 0;
  }
  if (left > right) {
    return 0;
  }
  if (left == tl && right == tr) {
    return tree[top];
  }
  long long tm = (tl + tr) >> 1;
  return Sum(top * 2, tl, tm, left, std::min(right, tm)) +
         Sum(top * 2 + 1, tm + 1, tr, std::max(left, tm + 1), right);
}

void Update(long long top, long long tl, long long tr, long long pos,
            long long delta) {
  if (tl == tr) {
    tree[top] += delta;
  } else {
    long long tm = (tl + tr) >> 1;
    if (pos <= tm) {
      Update(top * 2, tl, tm, pos, delta);
    } else {
      Update(top * 2 + 1, tm + 1, tr, pos, delta);
    }
    tree[top] = tree[top * 2] + tree[top * 2 + 1];
  }
}

int main() {
  long long cnt;
  std::cin >> cnt;
  std::vector<std::vector<long long>> requests(cnt,
                                               std::vector<long long>(3, 0));
  for (int i = 0; i < cnt; ++i) {
    std::string req;
    long long val;
    std::cin >> req >> val;
    if (req == "+") {
      requests[i] = {val, i + 1, 0};
    } else {
      requests[i] = {val, -i - 1, 0};
    }
  }
  std::sort(requests.begin(), requests.end());

  long long cmp = 1;
  for (int i = 0; i < cnt; ++i) {
    if (i > 0 && requests[i][0] > requests[i - 1][0]) {
      ++cmp;
    }
    requests[i][2] = cmp;
  }
  std::sort(requests.begin(), requests.end(),
            [](const auto& left, const auto& right) {
              return std::abs(left[1]) < std::abs(right[1]);
            });

  for (int i = 0; i < cnt; ++i) {
    if (requests[i][1] > 0) {
      Update(1, 1, cnt, requests[i][2], requests[i][0]);
    } else {
      std::cout << Sum(1, 1, cnt, 1, requests[i][2]) << "\n";
    }
  }
}