#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

int timer;
std::vector<int> tin;
std::vector<int> fup;
std::vector<int> answer;
std::map<std::pair<int, int>, int> edges_order;
std::map<std::pair<int, int>, bool> double_edges;

void Dfs(std::vector<std::vector<int>>& graph, std::vector<int>& colors,
         int top, int parent = -1) {
  colors[top] = 1;
  tin[top] = timer;
  fup[top] = timer++;
  for (size_t i = 0; i < graph[top].size(); ++i) {
    int vto = graph[top][i];
    if (vto == parent) {
      continue;
    }
    if (colors[vto] == 1) {
      fup[top] = std::min(fup[top], tin[vto]);
    } else {
      Dfs(graph, colors, vto, top);
      fup[top] = std::min(fup[top], fup[vto]);
      if (fup[vto] > tin[top] && !double_edges.contains({top, vto})) {
        answer.push_back(edges_order[{top, vto}]);
      }
    }
  }
}

int main() {
  int vertices;
  int edges;
  std::cin >> vertices >> edges;
  std::vector<std::vector<int>> graph(vertices, std::vector<int>());
  std::vector<int> colors(vertices, 0);
  tin.resize(vertices);
  fup.resize(vertices);
  for (int cnt = 1; cnt <= edges; ++cnt) {
    int top1;
    int top2;
    std::cin >> top1 >> top2;
    graph[top1 - 1].push_back(top2 - 1);
    graph[top2 - 1].push_back(top1 - 1);
    if (edges_order.contains({top2 - 1, top1 - 1})) {
      double_edges[{top2 - 1, top1 - 1}] = true;
      double_edges[{top1 - 1, top2 - 1}] = true;
    }
    edges_order[{top1 - 1, top2 - 1}] = cnt;
    edges_order[{top2 - 1, top1 - 1}] = cnt;
  }
  timer = 0;
  for (int top = 0; top < vertices; ++top) {
    if (colors[top] == 0) {
      Dfs(graph, colors, top);
    }
  }
  std::sort(answer.begin(), answer.end());
  std::cout << answer.size() << "\n";
  for (int bridge : answer) {
    std::cout << bridge << " ";
  }
}