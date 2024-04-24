#include <iostream>

struct Node {
  int key;
  Node* left;
  Node* right;
  int height;

  explicit Node(int key) : key(key), left(nullptr), right(nullptr), height(1) {}

  ~Node() {
    delete left;
    delete right;
  }
};

Node* CreateNode(int key) {
  Node* node = new Node(key);
  return (node);
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
  node->height = std::max(Height(node->left), Height(node->right)) + 1;
  temp1->height = std::max(Height(temp1->left), Height(temp1->right)) + 1;
  return temp1;
}

Node* LeftRotate(Node* node) {
  Node* temp1 = node->right;
  Node* temp2 = temp1->left;

  temp1->left = node;
  node->right = temp2;
  node->height = std::max(Height(node->left), Height(node->right)) + 1;
  temp1->height = std::max(Height(temp1->left), Height(temp1->right)) + 1;

  return temp1;
}

Node* Insert(Node* node, int key) {
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

int Search(Node* root, int speed) {
  Node* temp_node = root;
  int result = -1;
  while (temp_node != nullptr) {
    if (temp_node->key >= speed) {
      result = temp_node->key;
    }
    if (temp_node->key >= speed) {
      temp_node = temp_node->left;
    } else {
      temp_node = temp_node->right;
    }
  }
  return result;
}

int main() {
  int requests;
  std::cin >> requests;
  int yy = 0;
  const int kBase = 1000000000;
  Node* root = nullptr;
  for (int i = 0; i < requests; ++i) {
    std::string type;
    int speed;
    std::cin >> type >> speed;
    if (type == "+") {
      speed += yy;
      speed %= kBase;
      root = Insert(root, speed);
      yy = 0;
    } else {
      int result = Search(root, speed);
      std::cout << result << "\n";
      yy = result;
    }
  }
  delete root;
}