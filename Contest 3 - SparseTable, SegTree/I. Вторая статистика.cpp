#include <cmath>
#include <iostream>
#include <vector>

struct Node {
  long long first_min;
  int first_index;
  long long second_min;
  int second_index;
};

std::vector<std::vector<Node>> Build(std::vector<long long>& arr) {
  int sz = arr.size();
  int maxpow = int(log2(sz - 1));
  std::vector<std::vector<Node>> sparse_table(maxpow + 1,
                                              std::vector<Node>(sz));
  for (int i = 0; i < sz; ++i) {
    sparse_table[0][i].first_min = arr[i];
    sparse_table[0][i].first_index = i;
    sparse_table[0][i].second_min = arr[i];
    sparse_table[0][i].second_index = i;
  }
  for (int k = 0; k < maxpow; k++) {
    for (int ind = 0; ind + (1 << (k + 1)) <= sz; ind++) {
      int shift = ind + (1 << k);
      sparse_table[k + 1][ind].first_min = std::min(
          sparse_table[k][ind].first_min, sparse_table[k][shift].first_min);
      sparse_table[k + 1][ind].first_index =
          (sparse_table[k][ind].first_min >
           sparse_table[k][ind + (1 << k)].first_min)
              ? sparse_table[k][shift].first_index
              : sparse_table[k][ind].first_index;

      long long max1 = std::max(sparse_table[k][ind].first_min,
                                sparse_table[k][shift].first_min);
      long long ind_max1 = (sparse_table[k][ind].first_min <=
                            sparse_table[k][ind + (1 << k)].first_min)
                               ? sparse_table[k][shift].first_index
                               : sparse_table[k][ind].first_index;
      if (k == 0) {
        sparse_table[k + 1][ind].second_min = max1;
        sparse_table[k + 1][ind].second_index = ind_max1;
      } else {
        long long min2 = std::min(sparse_table[k][ind].second_min,
                                  sparse_table[k][shift].second_min);
        long long ind_min2 = (sparse_table[k][ind].second_min >
                              sparse_table[k][shift].second_min)
                                 ? sparse_table[k][shift].second_index
                                 : sparse_table[k][ind].second_index;
        sparse_table[k + 1][ind].second_min = std::min(min2, max1);
        sparse_table[k + 1][ind].second_index =
            (max1 > min2) ? ind_min2 : ind_max1;
      }
    }
  }
  return sparse_table;
}

long long SecondMin(std::vector<std::vector<Node>>& sparse, int left,
                    int right) {
  int pow = int(log2(right - left + 1));
  int shift = right - (1 << pow) + 1;
  if (sparse[pow][left].first_index == sparse[pow][shift].first_index) {
    return std::min(sparse[pow][left].second_min,
                    sparse[pow][shift].second_min);
  }
  long long max1 =
      std::max(sparse[pow][left].first_min, sparse[pow][shift].first_min);
  long long min2 =
      std::min(sparse[pow][left].second_min, sparse[pow][shift].second_min);
  return std::min(max1, min2);
}

int main() {
  int num;
  int ranges;
  std::cin >> num >> ranges;
  std::vector<long long> sequence(num);
  for (int i = 0; i < num; ++i) {
    std::cin >> sequence[i];
  }
  std::vector<std::vector<Node>> sparse_table = Build(sequence);

  for (int i = 0; i < ranges; ++i) {
    int left;
    int right;
    std::cin >> left >> right;
    std::cout << SecondMin(sparse_table, left - 1, right - 1) << "\n";
  }
}