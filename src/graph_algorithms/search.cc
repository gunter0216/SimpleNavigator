#include "s21_graph_algorithms.h"

auto GraphAlgorithms::breadthFirstSearch(Graph &graph, int startVertex)
    -> que_t {
  if (graph.empty()) throw std::invalid_argument("graph is empty");
  if (startVertex > graph.size() or startVertex < 1)
    throw std::out_of_range("wrong vertex");
  std::vector<bool> checked(graph.size(), false);
  que_t solution, tmp_q;
  tmp_q.push(startVertex);
  while (!tmp_q.empty()) {
    solution.push(tmp_q.peek());
    checked[tmp_q.peek() - 1] = true;
    que_t vertices = graph.allConnections(tmp_q.peek());
    while (!vertices.empty()) {
      if (!checked[vertices.peek() - 1]) tmp_q.push(vertices.peek());
      checked[vertices.peek() - 1] = true;
      vertices.pop();
    }
    tmp_q.pop();
  }
  return solution;
}

auto GraphAlgorithms::depthFirstSearch(Graph &graph, int startVertex) -> que_t {
  if (graph.empty()) throw std::invalid_argument("graph is empty");
  if (startVertex > graph.size() or startVertex < 1)
    throw std::out_of_range("wrong vertex");
  que_t solution{startVertex};
  DfsData.solution = &solution;
  DfsData.visited.resize(graph.size(), false);
  DfsData.graph = &graph;
  dfs_(startVertex);
  DfsData.visited.clear();
  DfsData.solution = nullptr;
  DfsData.graph = nullptr;
  return solution;
}

void GraphAlgorithms::dfs_(int n) {
  que_t vertices = DfsData.graph->allConnections(n);
  DfsData.visited[n - 1] = true;
  while (!vertices.empty()) {
    if (!DfsData.visited[vertices.peek() - 1]) {
      DfsData.solution->push(vertices.peek());
      dfs_(vertices.peek());
    }
    vertices.pop();
  }
}
