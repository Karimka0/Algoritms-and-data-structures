#include <iostream>
#include <queue>

class Heap {
  std::priority_queue<int64_t> max_heap_;
  std::priority_queue<int64_t, std::vector<int64_t>, std::greater<>> min_heap_;
  std::priority_queue<int64_t, std::vector<int64_t>, std::greater<>>
      del_max_heap_;
  std::priority_queue<int64_t> del_min_heap_;

 public:
  Heap() = default;
  void Insert(int64_t new_element) {
    max_heap_.push(new_element);
    min_heap_.push(new_element);
  }

  void Deleter() {
    while (!max_heap_.empty() && !del_min_heap_.empty() &&
           max_heap_.top() == del_min_heap_.top()) {
      max_heap_.pop();
      del_min_heap_.pop();
    }
    while (!min_heap_.empty() && !del_max_heap_.empty() &&
           min_heap_.top() == del_max_heap_.top()) {
      min_heap_.pop();
      del_max_heap_.pop();
    }
  }

  size_t Size() { return max_heap_.size() - del_min_heap_.size(); }

  void Clear() {
    while (!min_heap_.empty()) {
      min_heap_.pop();
    }
    while (!max_heap_.empty()) {
      max_heap_.pop();
    }
    while (!del_max_heap_.empty()) {
      del_max_heap_.pop();
    }
    while (!del_min_heap_.empty()) {
      del_min_heap_.pop();
    }
  }

  int64_t GetMin() { return min_heap_.top(); }

  int64_t GetMax() { return max_heap_.top(); }

  int64_t ExtractMin() {
    int64_t answer = min_heap_.top();
    del_min_heap_.push(min_heap_.top());
    min_heap_.pop();
    return answer;
  }

  int64_t ExtractMax() {
    int64_t answer = max_heap_.top();
    del_max_heap_.push(max_heap_.top());
    max_heap_.pop();
    return answer;
  }
};

int main() {
  int comands;
  std::cin >> comands;
  Heap heap;
  for (int i = 1; i <= comands; ++i) {
    heap.Deleter();
    std::string type;
    std::cin >> type;
    if (type == "insert") {
      int64_t new_element;
      std::cin >> new_element;
      heap.Insert(new_element);
      std::cout << "ok"
                << "\n";
    } else if (type == "size") {
      std::cout << heap.Size() << "\n";
    } else if (type == "clear") {
      heap.Clear();
      std::cout << "ok"
                << "\n";
    } else if (heap.Size() == 0) {
      std::cout << "error"
                << "\n";
    } else if (type == "get_max") {
      std::cout << heap.GetMax() << "\n";
    } else if (type == "get_min") {
      std::cout << heap.GetMin() << "\n";
    } else if (type == "extract_min") {
      std::cout << heap.ExtractMin() << "\n";
    } else if (type == "extract_max") {
      std::cout << heap.ExtractMax() << "\n";
    }
  }
}