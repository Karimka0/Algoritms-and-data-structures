#include <iostream>
#include <vector>

class UnionFind {
private:
    std::vector<int> parents_;
    std::vector<int> ranks_;

public:
    UnionFind(int cnt) {
        parents_.resize(cnt);
        ranks_.resize(cnt, 0);
        for (int top = 0; top < cnt; ++top) {
            parents_[top] = top;
        }
    }

    int Find(int top) {
        if (parents_[top] != top) {
            parents_[top] = Find(parents_[top]);
        }
        return parents_[top];
    }

    void UnionSets(int top1, int top2) {
        int root_x = Find(top1);
        int root_y = Find(top2);

        if (root_x != root_y) {
            if (ranks_[root_x] < ranks_[root_y]) {
                std::swap(root_x, root_y);
            }
            parents_[root_y] = root_x;
            if (ranks_[root_x] == ranks_[root_y]) {
                ++ranks_[root_x];
            }
        }
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int clones;
    int pairs;
    std::cin >> clones >> pairs;
    UnionFind unf(clones);
    for (int i = 0; i < pairs; ++i) {
        int top1;
        int top2;
        std::cin >> top1 >> top2;
        unf.UnionSets(top1 - 1, top2 - 1);
    }
    std::vector<std::vector<int>> groups(clones);
    for (int i = 0; i < clones; ++i) {
        int root = unf.Find(i);
        groups[root].push_back(i + 1);
    }
    int groups_cnt = 0;
    for (int i = 0; i < clones; ++i) {
        if (!groups[i].empty()) {
            ++groups_cnt;
        }
    }
    std::cout << groups_cnt << "\n";
    for (int i = 0; i < clones; ++i) {
        if(!groups[i].empty()) {
            std::cout << groups[i].size() << "\n";
            for (int top : groups[i]) {
                std::cout << top << " ";
            }
            std::cout << "\n";
        }
    }
}