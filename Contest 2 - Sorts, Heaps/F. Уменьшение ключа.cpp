#include <cstdint>
#include <iostream>
#include <vector>

class Heap {
  std::vector<std::pair<int, int64_t>> heap_;
  std::vector<int> heap_indexes_;
  int size_ = 0;

  void SiftUp(int index) {
    if (index == 1) {
      return;
    }
    int parent_index = index / 2;
    if (heap_[index].second < heap_[parent_index].second) {
      std::swap(heap_[index], heap_[parent_index]);
      std::swap(heap_indexes_[heap_[index].first],
                heap_indexes_[heap_[parent_index].first]);
      SiftUp(parent_index);
    }
  }

  void SiftDown(int index) {
    if (2 * index > size_) {
      return;
    }
    int son_index = 2 * index;
    if (son_index + 1 <= size_ &&
        heap_[son_index + 1].second < heap_[son_index].second) {
      ++son_index;
    }
    if (heap_[son_index].second < heap_[index].second) {
      std::swap(heap_[son_index], heap_[index]);
      std::swap(heap_indexes_[heap_[index].first],
                heap_indexes_[heap_[son_index].first]);
      SiftDown(son_index);
    }
  }

 public:
  Heap() {
    std::pair<int, int64_t> gag(0, 0);
    heap_.push_back(gag);
    heap_indexes_.push_back(0);
  }

  void Insert(int index, int64_t new_element) {
    ++size_;
    std::pair<int, int64_t> tup(index, new_element);
    heap_.push_back(tup);
    heap_indexes_.push_back(size_);
    SiftUp(size_);
  }

  int64_t GetMin() {
    heap_indexes_.push_back(0);
    return heap_[1].second;
  }

  void ExtractMin() {
    heap_indexes_.push_back(0);
    std::swap(heap_[1], heap_[size_]);
    std::swap(heap_indexes_[heap_[1].first], heap_indexes_[heap_[size_].first]);
    heap_.pop_back();
    --size_;
    SiftDown(1);
  }

  void DecreaseKey(int request, int64_t delta) {
    heap_indexes_.push_back(0);
    heap_[heap_indexes_[request]].second -= delta;
    SiftUp(heap_indexes_[request]);
  }
};

int main() {
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int requests;
  std::cin >> requests;
  Heap heap;
  for (int i = 1; i <= requests; ++i) {
    std::string type;
    std::cin >> type;
    if (type == "insert") {
      int64_t new_element;
      std::cin >> new_element;
      heap.Insert(i, new_element);
    } else if (type == "getMin") {
      int64_t min = heap.GetMin();
      std::cout << min << "\n";
    } else if (type == "extractMin") {
      heap.ExtractMin();
    } else if (type == "decreaseKey") {
      int request;
      int64_t delta;
      std::cin >> request >> delta;
      heap.DecreaseKey(request, delta);
    }
  }
}