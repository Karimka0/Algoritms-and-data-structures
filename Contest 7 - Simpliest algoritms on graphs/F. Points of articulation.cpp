//#include <algorithm>
//#include <iostream>
//#include <vector>
//#include <set>
//
//int timer;
//std::vector<int> tin;
//std::vector<int> fup;
//std::set<int> answer;
//
//
//void Dfs(std::vector<std::vector<int>>& graph, std::vector<int>& colors, int top, int parent = -1) {
//    colors[top] = 1;
//    tin[top] = timer;
//    fup[top] = timer++;
//    int children = 0;
//    for (size_t i = 0; i < graph[top].size(); ++i) {
//        int vto = graph[top][i];
//        if (vto == parent) {
//            continue;
//        }
//        if (colors[vto] != 0) {
//            fup[top] = std::min(fup[top], tin[vto]);
//        } else {
//            Dfs(graph, colors, vto, top);
//            fup[top] = std::min(fup[top], fup[vto]);
//            if (fup[vto] >= tin[top] && parent != -1) {
//                answer.insert(top);
//            }
//            ++children;
//        }
//    }
//    if (parent == -1 && children > 1) {
//        answer.insert(top);
//    }
//    colors[top] = 2;
//}
//
//int main() {
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
//    for (int i = 0; i < vertices; ++i) {
//        if (colors[i] == 0) {
//            Dfs(graph, colors, i);
//        }
//    }
//    std::cout << answer.size() << "\n";
//    for (int top: answer) {
//        std::cout << top + 1 << "\n";
//    }
//}