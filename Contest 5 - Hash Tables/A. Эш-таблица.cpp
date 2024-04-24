#include <iostream>
#include <list>
#include <vector>
const int kFirstSize = 8;

class HashTable {
  std::vector<std::list<int>> hash_table_;
  int size_ = kFirstSize;
  int elements_ = 0;
  const int kNum = 19;
  const int kDin = 20;

  int Hash(int xx) const { return xx % size_; }

  void Rehash() {
    int last_size = size_;
    size_ *= 2;
    std::vector<std::list<int>> new_hash_table(size_);
    for (int i = 0; i < last_size; ++i) {
      for (auto iter = hash_table_[i].begin(); iter != hash_table_[i].end();
           ++iter) {
        new_hash_table[Hash(*iter)].push_back(*iter);
      }
    }
    hash_table_ = new_hash_table;
  }

 public:
  HashTable() : hash_table_(kFirstSize) {}

  void Insert(int num) {
    if (!Find(num)) {
      ++elements_;
      hash_table_[Hash(num)].push_back(num);
    }
    if (kDin * elements_ > kNum * size_) {
      Rehash();
    }
  }

  bool Find(int num) {
    std::list<int>& list = hash_table_[Hash(num)];
    bool flag = false;
    auto first = list.begin();
    auto last = list.end();
    for (auto iter = first; iter != last; ++iter) {
      if (*iter == num) {
        flag = true;
        break;
      }
    }
    return flag;
  }

  void Erase(int num) {
    auto first = hash_table_[Hash(num)].begin();
    auto last = hash_table_[Hash(num)].end();
    for (auto iter = first; iter != last; ++iter) {
      if (*iter == num) {
        hash_table_[Hash(num)].erase(iter);
        --elements_;
        break;
      }
    }
  }
};

int main() {
  int cnt;
  std::cin >> cnt;
  std::string type;
  int num;
  HashTable table;
  for (int i = 0; i < cnt; ++i) {
    std::cin >> type >> num;
    if (type == "+") {
      table.Insert(num);
    } else if (type == "-") {
      table.Erase(num);
    } else {
      bool answer = table.Find(num);
      if (answer) {
        std::cout << "YES"
                  << "\n";
      } else {
        std::cout << "NO"
                  << "\n";
      }
    }
  }
}