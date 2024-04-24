#include <iostream>
#include <vector>

const long long cINF = 100000000000;

void Floyd(std::vector<std::vector<long long>>& graph,
           std::vector<std::vector<std::vector<long long>>>& paths) {
  for (size_t i = 0; i < graph.size(); ++i) {
    for (size_t u = 0; u < graph.size(); ++u) {
      for (size_t v = 0; v < graph.size(); ++v) {
        if (graph[u][v] > graph[u][i] + graph[i][v] && graph[u][i] != cINF &&
            graph[i][v] != cINF) {
          graph[u][v] = graph[u][i] + graph[i][v];
          if (paths[u][v].size() > graph.size()) {
            continue;
          }
          paths[u][v] = paths[u][i];
          std::vector<long long> copy = paths[i][v];
          std::copy(copy.begin(), copy.end(),
                    std::back_insert_iterator(paths[u][v]));
        }
      }
    }
  }
}

int main() {
  long long cities;
  long long flights;
  long long lecture_cnt;
  std::cin >> cities >> flights >> lecture_cnt;
  std::vector<std::vector<long long>> graph(
      cities, std::vector<long long>(cities, cINF));
  for (long long i = 0; i < cities; ++i) {
    graph[i][i] = 0;
  }
  std::vector<std::vector<std::vector<long long>>> paths(
      graph.size(), std::vector<std::vector<long long>>(graph.size()));
  for (long long i = 0; i < flights; ++i) {
    long long from;
    long long to;
    long long weight;
    std::cin >> from >> to >> weight;
    graph[from - 1][to - 1] = -weight;
    paths[from - 1][to - 1] = {i + 1};
  }
  std::vector<long long> lectures(lecture_cnt);
  for (long long i = 0; i < lecture_cnt; ++i) {
    std::cin >> lectures[i];
    --lectures[i];
  }
  Floyd(graph, paths);
  std::vector<long long> answer;
  for (long long i = 0; i < lecture_cnt - 1; ++i) {
    std::vector<long long> copy = paths[lectures[i]][lectures[i + 1]];
    std::copy(copy.begin(), copy.end(), std::back_insert_iterator(answer));
  }
  std::vector<std::vector<long long>> graph_copy = graph;
  Floyd(graph_copy, paths);
  bool check = false;
  for (long long i = 0; i < lecture_cnt - 1; ++i) {
    if (graph[lectures[i]][lectures[i + 1]] !=
        graph_copy[lectures[i]][lectures[i + 1]]) {
      check = true;
      break;
    }
  }
  if (check) {
    std::cout << "infinitely kind";
  } else {
    std::cout << answer.size() << "\n";
    for (long long i : answer) {
      std::cout << i << " ";
    }
  }
}