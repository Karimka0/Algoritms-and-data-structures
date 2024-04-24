#include <bits/stdc++.h>

#include <iostream>
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

struct Node {
  long long key;
  long long priority;
  Node* right;
  Node* left;
  long long len;
  long long size;

  Node(long long key, long long len)
      : key(key),
        priority(rng()),
        right(nullptr),
        left(nullptr),
        len(len),
        size(1) {}

  ~Node() {
    delete left;
    delete right;
  }
};

const long long kBase = 1000000001;

long long SizeOf(Node* root) {
  if (root == nullptr) {
    return 0;
  }
  return root->size;
}

void Resize(Node* root) {
  if (root != nullptr) {
    root->size = SizeOf(root->left) + SizeOf(root->right) + 1;
  }
}

Node* Merge(Node* left, Node* right) {
  if (left == nullptr) {
    return right;
  }
  if (right == nullptr) {
    return left;
  }
  Node* result;
  if (left->priority > right->priority) {
    left->right = Merge(left->right, right);
    result = left;
  } else {
    right->left = Merge(left, right->left);
    result = right;
  }
  Resize(result);
  return result;
}

std::pair<Node*, Node*> Split(Node* node, long long key) {
  if (node == nullptr) {
    return {nullptr, nullptr};
  }
  if (node->key <= key) {
    std::pair<Node*, Node*> temp = Split(node->right, key);
    node->right = temp.first;
    Resize(node);
    return {node, temp.second};
  }
  std::pair<Node*, Node*> temp = Split(node->left, key);
  node->left = temp.second;
  Resize(node);
  return {temp.first, node};
}

Node* Insert(Node* node, long long key, long long len) {
  std::pair<Node*, Node*> temp = Split(node, key);
  Node* top = new Node(key, len);
  Node* temp2 = Merge(top, temp.second);
  Resize(temp2);
  return Merge(temp.first, temp2);
}

Node* Erase(Node* node, long long key) {
  std::pair<Node*, Node*> temp = Split(node, key);
  std::pair<Node*, Node*> temp2 = Split(temp.first, key - 1);
  delete temp2.second;
  temp.first = temp2.first;
  Resize(temp.first);
  Resize(temp.second);
  return Merge(temp.first, temp.second);
}

std::pair<long long, long long> Kth(Node* root, long long pos) {
  if (root == nullptr) {
    return {kBase, kBase};
  }
  long long ord = SizeOf(root->left);
  std::pair<long long, long long> answer;
  if (ord == pos) {
    answer = {root->len, root->key};
  } else if (ord > pos) {
    answer = Kth(root->left, pos);
  } else {
    answer = Kth(root->right, pos - ord - 1);
  }
  return answer;
}

std::pair<Node*, long long> Build(Node* root, long long cnt) {
  long long sum2 = 0;
  long long pref_sum = 0;
  long long num;
  for (long long i = 0; i < cnt; ++i) {
    std::cin >> num;
    sum2 += num * num;
    pref_sum += num;
    root = Insert(root, pref_sum, num);
  }
  return {root, sum2};
}

int main() {
  long long cnt;
  long long pp;
  std::cin >> cnt >> pp;
  Node* root = nullptr;
  std::pair<Node*, long long> res = Build(root, cnt);
  root = res.first;
  long long sum2 = res.second;
  long long req;
  std::cin >> req;
  std::cout << sum2 << "\n";
  long long type;
  long long top;
  for (int i = 0; i < req; ++i) {
    std::cin >> type >> top;
    std::pair<long long, long long> middle = Kth(root, top - 1);
    if (type == 1) {
      std::pair<long long, long long> left = Kth(root, top - 2);
      std::pair<long long, long long> right = Kth(root, top);
      root = Erase(root, middle.second);
      sum2 -= middle.first * middle.first;
      if (left.first != kBase && right.first != kBase) {
        root = Erase(root, left.second);
        root = Erase(root, right.second);
        long long new_left = left.first + middle.first / 2;
        long long new_right = right.first + (middle.first + 1) / 2;
        root = Insert(root, left.second - left.first + new_left, new_left);
        root = Insert(root, right.second, new_right);
        sum2 -= (left.first * left.first + right.first * right.first);
        sum2 += new_left * new_left + new_right * new_right;
      } else if (left.first != kBase) {
        root = Erase(root, left.second);
        root = Insert(root, middle.second, left.first + middle.first);
        sum2 += (left.first + middle.first) * (left.first + middle.first) -
                left.first * left.first;
      } else if (right.first != kBase) {
        root = Erase(root, right.second);
        root = Insert(root, right.second, right.first + middle.first);
        sum2 += (right.first + middle.first) * (right.first + middle.first) -
                right.first * right.first;
      }
    } else if (type == 2) {
      root = Erase(root, middle.second);
      sum2 -= middle.first * middle.first;
      std::pair<long long, long long> new_left = {
          middle.first / 2, middle.second - (middle.first + 1) / 2};
      std::pair<long long, long long> new_right = {(middle.first + 1) / 2,
                                                   middle.second};
      sum2 +=
          new_left.first * new_left.first + new_right.first * new_right.first;
      root = Insert(root, new_right.second, new_right.first);
      root = Insert(root, new_left.second, new_left.first);
    }
    std::cout << sum2 << "\n";
  }
  delete root;
}