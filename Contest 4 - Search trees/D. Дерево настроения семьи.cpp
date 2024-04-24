#include <iostream>

struct Node {
  long long key;
  long long priority;
  int size;
  Node* right;
  Node* left;

  Node(long long key)
      : key(key), priority(rand()), size(1), right(nullptr), left(nullptr) {}

  ~Node() {
    delete left;
    delete right;
  }
};

const long long kBase = 1000000001;

int SizeOf(Node* root) {
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

Node* Insert(Node* node, long long key) {
  std::pair<Node*, Node*> temp = Split(node, key);
  Node* top = new Node(key);
  return Merge(temp.first, Merge(top, temp.second));
}

Node* Erase(Node* node, long long key) {
  std::pair<Node*, Node*> temp = Split(node, key);
  std::pair<Node*, Node*> temp2 = Split(temp.first, key - 1);
  delete temp2.second;
  temp.first = temp2.first;
  return Merge(temp.first, temp.second);
}

bool Exist(Node* node, long long key) {
  if (node == nullptr) {
    return false;
  }
  if (node->key == key) {
    return true;
  }
  if (node->key > key) {
    return Exist(node->left, key);
  }
  return Exist(node->right, key);
}

long long Next(Node* node, long long key) {
  long long answer = kBase;
  Node* temp_node = node;
  while (temp_node != nullptr) {
    if (temp_node->key <= key) {
      temp_node = temp_node->right;
    } else {
      answer = temp_node->key;
      temp_node = temp_node->left;
    }
  }
  return answer;
}

long long Prev(Node* node, long long key) {
  long long answer = kBase;
  Node* temp_node = node;
  while (temp_node != nullptr) {
    if (temp_node->key < key) {
      answer = temp_node->key;
      temp_node = temp_node->right;
    } else {
      temp_node = temp_node->left;
    }
  }
  return answer;
}

long long Kth(Node* root, long long key) {
  if (root == nullptr) {
    return kBase;
  }
  int ord = SizeOf(root->left);
  long long answer;
  if (ord == key) {
    answer = root->key;
  } else if (ord > key) {
    answer = Kth(root->left, key);
  } else {
    answer = Kth(root->right, key - ord - 1);
  }
  return answer;
}

int main() {
  std::string command;
  long long val;
  Node* root = nullptr;
  while (std::cin >> command >> val) {
    if (command == "insert") {
      root = Insert(root, val);
    } else if (command == "delete") {
      root = Erase(root, val);
    } else if (command == "exists") {
      if (Exist(root, val)) {
        std::cout << "true"
                  << "\n";
      } else {
        std::cout << "false"
                  << "\n";
      }
    } else if (command == "next") {
      long long answer = Next(root, val);
      if (answer == kBase) {
        std::cout << "none"
                  << "\n";
      } else {
        std::cout << answer << "\n";
      }
    } else if (command == "prev") {
      long long answer = Prev(root, val);
      if (answer == kBase) {
        std::cout << "none"
                  << "\n";
      } else {
        std::cout << answer << "\n";
      }
    } else if (command == "kth") {
      long long answer = Kth(root, val);
      if (answer == kBase) {
        std::cout << "none"
                  << "\n";
      } else {
        std::cout << answer << "\n";
      }
    }
  }
  delete root;
}