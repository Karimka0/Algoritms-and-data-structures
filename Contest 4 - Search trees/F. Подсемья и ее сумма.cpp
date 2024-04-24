#include <iostream>

struct Node {
  long long key;
  long long sum;
  Node* left;
  Node* right;
  int height;

  explicit Node(long long key)
      : key(key), sum(key), left(nullptr), right(nullptr), height(1) {}

  ~Node() {
    delete left;
    delete right;
  }
};

Node* CreateNode(long long key) {
  Node* node = new Node(key);
  return (node);
}

long long Sum(Node* node) {
  if (node == nullptr) {
    return 0;
  }
  return node->sum;
}

int Height(Node* node) {
  if (node == nullptr) {
    return 0;
  }
  return node->height;
}

int BalanceFactor(Node* node) {
  if (node == nullptr) {
    return 0;
  }
  return Height(node->left) - Height(node->right);
}

Node* RightRotate(Node* node) {
  Node* temp1 = node->left;
  Node* temp2 = temp1->right;
  temp1->right = node;
  node->left = temp2;
  node->sum = Sum(temp2) + Sum(node->right) + node->key;
  temp1->sum = Sum(temp1->left) + Sum(node) + temp1->key;
  node->height = std::max(Height(node->left), Height(node->right)) + 1;
  temp1->height = std::max(Height(temp1->left), Height(temp1->right)) + 1;
  return temp1;
}

Node* LeftRotate(Node* node) {
  Node* temp1 = node->right;
  Node* temp2 = temp1->left;
  temp1->left = node;
  node->right = temp2;
  node->sum = Sum(node->left) + Sum(temp2) + node->key;
  temp1->sum = Sum(node) + Sum(temp1->right) + temp1->key;
  node->height = std::max(Height(node->left), Height(node->right)) + 1;
  temp1->height = std::max(Height(temp1->left), Height(temp1->right)) + 1;
  return temp1;
}

Node* Insert(Node* node, long long key) {
  if (node == nullptr) {
    return (CreateNode(key));
  }
  if (key < node->key) {
    node->left = Insert(node->left, key);
  } else if (key > node->key) {
    node->right = Insert(node->right, key);
  } else {
    return node;
  }

  node->height = 1 + std::max(Height(node->left), Height(node->right));
  node->sum = Sum(node->left) + Sum(node->right) + node->key;

  int balance = BalanceFactor(node);
  if (balance == 2 && key < node->left->key) {
    return RightRotate(node);
  }
  if (balance == -2 && key > node->right->key) {
    return LeftRotate(node);
  }
  if (balance == 2 && key > node->left->key) {
    node->left = LeftRotate(node->left);
    return RightRotate(node);
  }
  if (balance == -2 && key < node->right->key) {
    node->right = RightRotate(node->right);
    return LeftRotate(node);
  }
  return node;
}

long long LeftSum(Node* root, long long left) {
  Node* temp_node = root;
  long long result = 0;
  while (temp_node != nullptr) {
    if (temp_node->key == left) {
      result += Sum(temp_node->left);
      break;
    }
    if (temp_node->key > left) {
      temp_node = temp_node->left;
    } else {
      result += temp_node->key;
      result += Sum(temp_node->left);
      temp_node = temp_node->right;
    }
  }
  return result;
}

long long RightSum(Node* root, long long right) {
  Node* temp_node = root;
  long long result = 0;
  while (temp_node != nullptr) {
    if (temp_node->key == right) {
      result += Sum(temp_node->right);
      break;
    }
    if (temp_node->key < right) {
      temp_node = temp_node->right;
    } else {
      result += temp_node->key;
      result += Sum(temp_node->right);
      temp_node = temp_node->left;
    }
  }
  return result;
}

int main() {
  int requests;
  std::cin >> requests;
  long long yy = 0;
  const int kBase = 1000000000;
  Node* root = nullptr;
  for (int i = 0; i < requests; ++i) {
    std::string type;
    std::cin >> type;
    if (type == "+") {
      long long mood;
      std::cin >> mood;
      root = Insert(root, (mood + yy) % kBase);
      yy = 0;
    } else {
      long long left_mood;
      long long right_mood;
      std::cin >> left_mood >> right_mood;
      long long answer =
          Sum(root) - LeftSum(root, left_mood) - RightSum(root, right_mood);
      std::cout << answer << "\n";
      yy = answer;
    }
  }
  delete root;
}