#include <iostream>
#include <vector>

struct Node {
  long long key;
  Node* left;
  Node* right;
  long long height;
  long long repeats;
  long long elements;

  explicit Node(long long key)
      : key(key),
        left(nullptr),
        right(nullptr),
        height(1),
        repeats(1),
        elements(1) {}

  ~Node() {
    delete left;
    delete right;
  }
};

const int kMaxSize = 4 * 100001;
Node* tree[kMaxSize];
long long xx;
long long yy;
long long delta;

long long Amount(Node* node) {
  if (node == nullptr) {
    return 0;
  }
  return node->elements;
}

Node* CreateNode(long long key) {
  Node* node = new Node(key);
  return node;
}

long long Height(Node* node) {
  if (node == nullptr) {
    return 0;
  }
  return node->height;
}

long long BalanceFactor(Node* node) {
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
  node->elements = Amount(temp2) + Amount(node->right) + node->repeats;
  temp1->elements = Amount(temp1->left) + Amount(node) + temp1->repeats;
  node->height = std::max(Height(node->left), Height(node->right)) + 1;
  temp1->height = std::max(Height(temp1->left), Height(temp1->right)) + 1;
  return temp1;
}

Node* LeftRotate(Node* node) {
  Node* temp1 = node->right;
  Node* temp2 = temp1->left;
  temp1->left = node;
  node->right = temp2;
  node->elements = Amount(node->left) + Amount(temp2) + node->repeats;
  temp1->elements = Amount(node) + Amount(temp1->right) + temp1->repeats;
  node->height = std::max(Height(node->left), Height(node->right)) + 1;
  temp1->height = std::max(Height(temp1->left), Height(temp1->right)) + 1;
  return temp1;
}

Node* Insert(Node* node, long long key) {
  if (node == nullptr) {
    return (CreateNode(key));
  }
  ++node->elements;
  if (key < node->key) {
    node->left = Insert(node->left, key);
  } else if (key > node->key) {
    node->right = Insert(node->right, key);
  } else {
    ++node->repeats;
    return node;
  }

  node->height = 1 + std::max(Height(node->left), Height(node->right));
  long long balance = BalanceFactor(node);
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

Node* MinNode(Node* node) {
  Node* min_node = node;
  while (min_node->left != nullptr) {
    min_node = min_node->left;
  }
  return min_node;
}

Node* Balancing(Node* root) {
  long long balance = BalanceFactor(root);
  if (balance > 1 && BalanceFactor(root->left) >= 0) {
    return RightRotate(root);
  }
  if (balance > 1 && BalanceFactor(root->left) < 0) {
    root->left = LeftRotate(root->left);
    return RightRotate(root);
  }
  if (balance < -1 && BalanceFactor(root->right) <= 0) {
    return LeftRotate(root);
  }
  if (balance < -1 && BalanceFactor(root->right) > 0) {
    root->right = RightRotate(root->right);
    return LeftRotate(root);
  }
  return root;
}

Node* DeleteMin(Node* node, long long reps) {
  if (node->left == nullptr) {
    Node* temp = node->right;
    node->right = nullptr;
    delete node;
    return temp;
  }
  node->elements -= reps;
  node->left = DeleteMin(node->left, reps);
  node->height = 1 + std::max(Height(node->left), Height(node->right));
  return Balancing(node);
}

Node* Delete(Node* root, long long key) {
  if (root == nullptr) {
    return root;
  }
  if (key < root->key) {
    --root->elements;
    root->left = Delete(root->left, key);
  } else if (key > root->key) {
    --root->elements;
    root->right = Delete(root->right, key);
  } else {
    if (root->repeats > 1) {
      --root->repeats;
      --root->elements;
      return root;
    }
    if ((root->left == nullptr) || (root->right == nullptr)) {
      if ((root->left == nullptr) && (root->right == nullptr)) {
        delete root;
        root = nullptr;
      } else if (root->left == nullptr) {
        Node* temp = root->right;
        root->right = nullptr;
        delete root;
        return temp;
      } else if (root->right == nullptr) {
        Node* temp = root->left;
        root->left = nullptr;
        delete root;
        return temp;
      }
    } else {
      Node* temp = MinNode(root->right);
      root->key = temp->key;
      --root->elements;
      root->repeats = temp->repeats;
      root->right = DeleteMin(root->right, temp->repeats);
    }
  }
  if (root == nullptr) {
    return root;
  }

  root->height = 1 + std::max(Height(root->left), Height(root->right));
  return Balancing(root);
}

long long LeftAmount(Node* root, int left) {
  Node* temp_node = root;
  long long result = 0;
  while (temp_node != nullptr) {
    if (temp_node->key == left) {
      result += Amount(temp_node->left);
      break;
    }
    if (temp_node->key > left) {
      temp_node = temp_node->left;
    } else {
      result += temp_node->repeats;
      result += Amount(temp_node->left);
      temp_node = temp_node->right;
    }
  }
  return result;
}

long long RightAmount(Node* root, int right) {
  Node* temp_node = root;
  long long result = 0;
  while (temp_node != nullptr) {
    if (temp_node->key == right) {
      result += Amount(temp_node->right);
      break;
    }
    if (temp_node->key < right) {
      temp_node = temp_node->right;
    } else {
      result += temp_node->repeats;
      result += Amount(temp_node->right);
      temp_node = temp_node->left;
    }
  }
  return result;
}

long long AllAmount(Node* root, int left, int right) {
  return root->elements - LeftAmount(root, left) - RightAmount(root, right);
}

Node* Add(Node* node1, Node* node2) {
  if (node2 == nullptr) {
    return node1;
  }
  for (long long i = 0; i < node2->repeats; ++i) {
    node1 = Insert(node1, node2->key);
  }
  node1 = Add(node1, node2->left);
  node1 = Add(node1, node2->right);
  return node1;
}

void Build(std::vector<int>& leaves, int top, int tl, int tr) {
  if (tl == tr) {
    Node* node = CreateNode(leaves[tl]);
    tree[top] = node;
  } else {
    int tm = (tl + tr) >> 1;
    Build(leaves, top * 2, tl, tm);
    Build(leaves, top * 2 + 1, tm + 1, tr);
    tree[top] = Add(tree[top], tree[2 * top]);
    tree[top] = Add(tree[top], tree[top * 2 + 1]);
  }
}

long long GetAmount(int top, int tl, int tr, int left, int right) {
  if (left > right) {
    return 0;
  }
  if (left == tl && right == tr) {
    return AllAmount(tree[top], xx, yy);
  }
  int tm = (tl + tr) >> 1;
  return GetAmount(top * 2, tl, tm, left, std::min(right, tm)) +
         GetAmount(top * 2 + 1, tm + 1, tr, std::max(left, tm + 1), right);
}

void Update(int top, int tl, int tr, int pos, std::vector<int>& powers) {
  if (tl == tr) {
    tree[top]->key = delta;
  } else {
    int tm = (tl + tr) >> 1;
    if (pos <= tm) {
      Update(top * 2, tl, tm, pos, powers);
    } else {
      Update(top * 2 + 1, tm + 1, tr, pos, powers);
    }
    tree[top] = Delete(tree[top], powers[pos]);
    tree[top] = Insert(tree[top], delta);
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int cnt;
  int req;
  std::cin >> cnt >> req;
  std::vector<int> powers(cnt + 1);
  for (int i = 1; i <= cnt; ++i) {
    std::cin >> powers[i];
  }
  Build(powers, 1, 1, cnt);
  std::string type;
  for (int i = 0; i < req; ++i) {
    std::cin >> type;
    if (type == "GET") {
      int left;
      int right;
      std::cin >> left >> right >> xx >> yy;
      std::cout << GetAmount(1, 1, cnt, left, right) << "\n";
    } else {
      int index;
      std::cin >> index >> delta;
      Update(1, 1, cnt, index, powers);
      powers[index] = delta;
    }
  }
  for (int i = 1; i < cnt * 4; ++i) {
    delete tree[i];
  }
}