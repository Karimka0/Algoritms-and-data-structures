//#include <algorithm>
//#include <iostream>
//#include <vector>
//#include <map>
//#include <set>
//
//class UnionFind {
//private:
//    std::vector<int> parents_;
//    std::vector<int> ranks_;
//
//public:
//    UnionFind(int cnt) {
//        parents_.resize(cnt);
//        ranks_.resize(cnt, 0);
//        for (int top = 0; top < cnt; ++top) {
//            parents_[top] = top;
//        }
//    }
//
//    int Find(int top) {
//        if (parents_[top] != top) {
//            parents_[top] = Find(parents_[top]);
//        }
//        return parents_[top];
//    }
//
//    void UnionSets(int top1, int top2) {
//        int root_x = Find(top1);
//        int root_y = Find(top2);
//
//        if (root_x != root_y) {
//            if (ranks_[root_x] < ranks_[root_y]) {
//                std::swap(root_x, root_y);
//            }
//            parents_[root_y] = root_x;
//            if (ranks_[root_x] == ranks_[root_y]) {
//                ++ranks_[root_x];
//            }
//        }
//    }
//};
//
//int timer;
//std::vector<int> tin;
//std::vector<int> fup;
//std::set<std::pair<int, int>> bridges;
//
//void Dfs(std::vector<std::vector<int>>& graph, std::vector<int>& colors, int top, int parent = -1) {
//    colors[top] = 1;
//    tin[top] = timer;
//    fup[top] = timer++;
//    for (size_t i = 0; i < graph[top].size(); ++i) {
//        int vto = graph[top][i];
//        if (vto == parent) {
//            continue;
//        }
//        if (colors[vto] == 1) {
//            fup[top] = std::min(fup[top], tin[vto]);
//        } else {
//            Dfs(graph, colors, vto, top);
//            fup[top] = std::min(fup[top], fup[vto]);
//            if (fup[vto] > tin[top]) {
//                bridges.insert({top, vto});
//                bridges.insert({vto, top});
//            }
//        }
//    }
//}
//
//int main() {
//    std::ios::sync_with_stdio(false);
//    std::cin.tie(nullptr);
//    int vertices;
//    int edges;
//    std::cin >> vertices >> edges;
//    std::vector<std::vector<int>> graph(vertices, std::vector<int>());
//    std::vector<int> colors(vertices, 0);
//    tin.resize(vertices);
//    fup.resize(vertices);
//    for (int cnt = 1; cnt <= edges; ++cnt) {
//        int top1;
//        int top2;
//        std::cin >> top1 >> top2;
//        graph[top1 - 1].push_back(top2 - 1);
//        graph[top2 - 1].push_back(top1 - 1);
//    }
//    timer = 0;
//    for (int top = 0; top < vertices; ++top) {
//        if (colors[top] == 0) {
//            Dfs(graph, colors, top);
//        }
//    }
//    UnionFind unf(vertices);
//    std::vector<std::vector<int>> graph2(vertices, std::vector<int>());
//    for (int i = 0; i < vertices; ++i) {
//        for (size_t j = 0; j < graph[i].size(); ++j) {
//            if (!bridges.contains({i, graph[i][j]})) {
//                unf.UnionSets(i, graph[i][j]);
//            } else  {
//                graph2[i].push_back(graph[i][j]);
//            }
//        }
//    }
//    std::vector<std::vector<int>> groups(vertices);
//    for (int top = 0; top < vertices; ++top) {
//        int root = unf.Find(top);
//        groups[root].push_back(top);
//    }
//    int leaves_cnt = 0;
//    for (int i = 0; i < vertices; ++i) {
//        size_t group_deg = 0;
//        for (size_t j = 0; j < groups[i].size(); ++j) {
//            group_deg += graph2[groups[i][j]].size();
//        }
//        if (group_deg == 1) {
//            ++leaves_cnt;
//        }
//    }
//    int answer = (leaves_cnt + 1) / 2;
//    std::cout << answer << "\n";
//}