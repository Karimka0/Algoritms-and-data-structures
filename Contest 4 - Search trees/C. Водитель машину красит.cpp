#include <iostream>
#include <vector>

struct Node {
  std::string name;
  int index;
  Node* left;
  Node* right;
  int height;

  explicit Node(std::string name, int index)
      : name(std::move(name)),
        index(index),
        left(nullptr),
        right(nullptr),
        height(1) {}

  ~Node() {
    delete left;
    delete right;
  }
};

Node* CreateNode(std::string name, int index) {
  Node* node = new Node(std::move(name), index);
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

Node* Insert(Node* node, const std::string& name, int index) {
  if (node == nullptr) {
    return (CreateNode(name, index));
  }
  if (name < node->name) {
    node->left = Insert(node->left, name, index);
  } else if (name > node->name) {
    node->right = Insert(node->right, name, index);
  } else {
    return node;
  }

  node->height = 1 + std::max(Height(node->left), Height(node->right));

  int balance = BalanceFactor(node);
  if (balance == 2 && name < node->left->name) {
    return RightRotate(node);
  }
  if (balance == -2 && name > node->right->name) {
    return LeftRotate(node);
  }
  if (balance == 2 && name > node->left->name) {
    node->left = LeftRotate(node->left);
    return RightRotate(node);
  }
  if (balance == -2 && name < node->right->name) {
    node->right = RightRotate(node->right);
    return LeftRotate(node);
  }
  return node;
}

int Search(Node* root, const std::string& name) {
  Node* temp_node = root;
  int result = -1;
  while (temp_node != nullptr) {
    if (temp_node->name == name) {
      result = temp_node->index;
    }
    if (temp_node->name >= name) {
      temp_node = temp_node->left;
    } else {
      temp_node = temp_node->right;
    }
  }
  return result;
}

int main() {
  int cnt;
  std::cin >> cnt;
  Node* racers_tree = nullptr;
  std::vector<std::string> racers_array(cnt);
  Node* cars_tree = nullptr;
  std::vector<std::string> car_array(cnt);
  for (int i = 0; i < cnt; ++i) {
    std::cin >> racers_array[i] >> car_array[i];
    racers_tree = Insert(racers_tree, racers_array[i], i);
    cars_tree = Insert(cars_tree, car_array[i], i);
  }
  int requests;
  std::cin >> requests;
  std::string name;
  for (int i = 0; i < requests; ++i) {
    std::cin >> name;
    int res1 = Search(racers_tree, name);
    int res2 = Search(cars_tree, name);
    if (res1 != -1) {
      std::cout << car_array[res1] << "\n";
    } else {
      std::cout << racers_array[res2] << "\n";
    }
  }
  delete racers_tree;
  delete cars_tree;
}