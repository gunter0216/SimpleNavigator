#include <set>

#include "s21_graph_algorithms.h"

auto GraphAlgorithms::getLeastSpanningTree(Graph &graph) -> Graph {
  if (graph.empty()) throw std::invalid_argument("graph is empty");
  if (graph.size() < 1)
    throw std::invalid_argument("too small for spanning tree");
  Graph result;
  matr_t res_matr(graph.size(), graph.size());
  std::set<int> visited;
  std::set<int> unvisited;
  for (int i = 2; i <= graph.size(); ++i) unvisited.insert(i);
  visited.insert(1);
  while (!unvisited.empty()) {
    int min = INT32_MAX;
    std::pair<int, int> edge;
    for (auto i : visited) {
      for (int j = 1; j <= graph.size(); ++j) {
        if (!visited.count(j) && graph.distBetween(i, j) &&
            graph.distBetween(i, j) < min) {
          min = graph.distBetween(i, j);
          edge = {i, j};
        }
      }
    }
    unvisited.erase(edge.second);
    visited.insert(edge.second);
    res_matr(edge.first - 1, edge.second - 1) =
        res_matr(edge.second - 1, edge.first - 1) = min;
  }
  result.setMatrix(res_matr);
  return result;
}
