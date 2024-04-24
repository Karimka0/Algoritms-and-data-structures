#include <iostream>
#include <vector>

std::vector<size_t> sorted_tops;
std::vector<size_t> now_component;

void Dfs1(std::vector<std::vector<size_t>>& graph, std::vector<int>& colors,
          size_t top) {
  colors[top] = 1;
  for (size_t i = 0; i < graph[top].size(); ++i) {
    if (colors[graph[top][i]] == 0) {
      Dfs1(graph, colors, graph[top][i]);
    }
  }
  sorted_tops.push_back(top);
}

void Dfs2(std::vector<std::vector<size_t>>& inverted_graph,
          std::vector<int>& colors, size_t top) {
  colors[top] = 1;
  now_component.push_back(top);
  for (size_t i = 0; i < inverted_graph[top].size(); ++i) {
    if (colors[inverted_graph[top][i]] == 0) {
      Dfs2(inverted_graph, colors, inverted_graph[top][i]);
    }
  }
}

int main() {
  int vertices;
  int edges;
  std::cin >> vertices >> edges;
  std::vector<std::vector<size_t>> graph(vertices, std::vector<size_t>());
  std::vector<std::vector<size_t>> inverted_graph(vertices,
                                                  std::vector<size_t>());
  std::vector<int> colors(vertices, 0);
  for (int i = 0; i < edges; ++i) {
    int top1;
    int top2;
    std::cin >> top1 >> top2;
    graph[top1 - 1].push_back(top2 - 1);
    inverted_graph[top2 - 1].push_back(top1 - 1);
  }
  for (int top = 0; top < vertices; ++top) {
    if (colors[top] == 0) {
      Dfs1(graph, colors, top);
    }
  }
  colors.assign(vertices, 0);
  int components_cnt = 0;
  std::vector<size_t> answer(vertices, 0);
  for (int top1 = 0; top1 < vertices; ++top1) {
    size_t top2 = sorted_tops[vertices - top1 - 1];
    if (colors[top2] == 0) {
      Dfs2(inverted_graph, colors, top2);
      ++components_cnt;
      for (unsigned long vert : now_component) {
        answer[vert] = components_cnt;
      }
      now_component.clear();
    }
  }
  std::cout << components_cnt << "\n";
  for (size_t top : answer) {
    std::cout << top << " ";
  }
}