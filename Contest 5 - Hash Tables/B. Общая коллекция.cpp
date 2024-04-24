#include <iostream>
#include <list>
#include <vector>
const int kFirstSize = 8;

class HashTable {
  std::vector<std::list<std::pair<int, int>>> hash_table_;
  int size_ = kFirstSize;
  int elements_ = 0;
  const int kNum = 19;
  const int kDin = 20;

  int Hash(int xx) const { return xx % size_; }

  void Rehash() {
    int last_size = size_;
    size_ *= 2;
    std::vector<std::list<std::pair<int, int>>> new_hash_table(size_);
    for (int i = 0; i < last_size; ++i) {
      for (auto iter = hash_table_[i].begin(); iter != hash_table_[i].end();
           ++iter) {
        new_hash_table[Hash(iter->first)].emplace_back(iter->first,
                                                       iter->second);
      }
    }
    hash_table_ = new_hash_table;
  }

 public:
  HashTable() : hash_table_(kFirstSize) {}

  bool Check(int num) {
    bool flag = false;
    auto first = hash_table_[Hash(num)].begin();
    auto last = hash_table_[Hash(num)].end();
    for (auto iter = first; iter != last; ++iter) {
      if (iter->first == num) {
        flag = true;
        if (iter->second > 1) {
          --iter->second;
        } else {
          hash_table_[Hash(num)].erase(iter);
        }
        break;
      }
    }
    return flag;
  }

  void Insert(int num) {
    bool flag = false;
    auto first = hash_table_[Hash(num)].begin();
    auto last = hash_table_[Hash(num)].end();
    for (auto iter = first; iter != last; ++iter) {
      if (iter->first == num) {
        flag = true;
        ++iter->second;
        break;
      }
    }
    if (!flag) {
      hash_table_[Hash(num)].emplace_back(num, 1);
      ++elements_;
    }
    if (kDin * elements_ > kNum * size_) {
      Rehash();
    }
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int cnt1;
  std::cin >> cnt1;
  int num;
  HashTable hash_table1;
  for (int i = 0; i < cnt1; ++i) {
    std::cin >> num;
    hash_table1.Insert(num);
  }
  int cnt2;
  std::cin >> cnt2;
  std::vector<int> answer;
  for (int i = 0; i < cnt2; ++i) {
    std::cin >> num;
    if (hash_table1.Check(num)) {
      answer.push_back(num);
    }
  }
  std::cout << answer.size() << "\n";
  for (int ii : answer) {
    std::cout << ii << " ";
  }
}