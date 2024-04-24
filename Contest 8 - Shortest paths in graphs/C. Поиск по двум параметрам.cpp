#include <iostream>
#include <queue>
#include <vector>

const size_t cINF = 2009000999;
size_t max_time;

void Dijkstra(std::vector<std::vector<std::pair<size_t, size_t>>>& graph,
              size_t start) {
  std::priority_queue<std::pair<size_t, size_t>,
                      std::vector<std::pair<size_t, size_t>>, std::greater<>>
      heap;
  std::vector<size_t> prev(graph.size() * (max_time + 1), cINF);
  std::vector<size_t> dist(graph.size() * (max_time + 1), cINF);
  dist[start] = 0;
  heap.emplace(0, start);
  while (!heap.empty()) {
    size_t now_dist = heap.top().first;
    size_t top = heap.top().second;
    heap.pop();
    if (now_dist > dist[top]) {
      continue;
    }
    size_t index = top % graph.size();
    for (const auto& edge : graph[index]) {
      size_t v = edge.second + top - index;
      size_t weight = edge.first;
      if (v >= dist.size()) {
        continue;
      }
      if (dist[v] > dist[top] + weight) {
        dist[v] = dist[top] + weight;
        prev[v] = top;
        heap.emplace(dist[v], v);
      }
    }
  }
  size_t answer = cINF;
  size_t now_top;
  for (size_t i = graph.size() - 1; i < dist.size(); i += graph.size()) {
    if (dist[i] < answer) {
      answer = dist[i];
      now_top = i;
    }
  }
  if (answer == cINF) {
    std::cout << -1;
  } else {
    std::cout << answer << std::endl;
    std::vector<size_t> cycle;
    for (;; now_top = prev[now_top]) {
      cycle.push_back(now_top);
      if (now_top == 0) {
        break;
      }
    }
    std::cout << cycle.size() << std::endl;
    for (size_t i = cycle.size(); i != 0; --i) {
      std::cout << cycle[i - 1] % graph.size() + 1 << " ";
    }
  }
}

int main() {
  size_t vertexes;
  size_t edges;
  std::cin >> vertexes >> edges >> max_time;
  std::vector<std::vector<std::pair<size_t, size_t>>> graph(
      vertexes, std::vector<std::pair<size_t, size_t>>());
  for (size_t i = 0; i < edges; ++i) {
    size_t from;
    size_t to;
    size_t cost;
    size_t time;
    std::cin >> from >> to >> cost >> time;
    --from;
    --to;
    graph[from].emplace_back(cost, time * vertexes + to);
    graph[to].emplace_back(cost, time * vertexes + from);
  }
  Dijkstra(graph, 0);
}