#include <algorithm>
#include <iostream>
#include <vector>

void SiftUp(std::vector<long long>& heap, int index) {
  if (index == 1) {
    return;
  }
  int parent_index = index / 2;
  if (heap[index] > heap[parent_index]) {
    std::swap(heap[index], heap[parent_index]);
    SiftUp(heap, parent_index);
  }
}

void SiftDown(std::vector<long long>& heap, int index, int size) {
  if (2 * index > size) {
    return;
  }
  int son_index = 2 * index;
  if (son_index + 1 <= size && heap[son_index + 1] > heap[son_index]) {
    son_index++;
  }
  if (heap[son_index] > heap[index]) {
    std::swap(heap[son_index], heap[index]);
    SiftDown(heap, son_index, size);
  }
}

int main() {
  int cnt;
  int mins;
  long long a0;
  long long xx;
  long long yy;
  std::cin >> cnt >> mins >> a0 >> xx >> yy;
  std::vector<long long> heap;
  heap.push_back(0);
  const int kBase = 1073741824;
  int size = 0;
  for (int i = 1; i <= mins; i++) {
    a0 = (xx * a0 + yy) % kBase;
    heap.push_back(a0);
    size++;
    SiftUp(heap, size);
  }
  for (int i = mins + 1; i <= cnt; i++) {
    a0 = (xx * a0 + yy) % kBase;
    if (a0 < heap[1]) {
      heap[1] = a0;
      SiftDown(heap, 1, size);
    }
  }
  std::sort(heap.begin() + 1, heap.end());
  for (int i = 1; i < size + 1; i++) {
    std::cout << heap[i] << " ";
  }
}