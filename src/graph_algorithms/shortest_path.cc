#include "s21_graph_algorithms.h"

auto GraphAlgorithms::getShortestPathBetweenVertices(Graph &graph, int vertex1,
                                                     int vertex2) -> unsigned {
  if (graph.empty()) throw std::invalid_argument("graph is empty");
  if (graph.info() & Graph::kNegativeEdge)
    throw std::invalid_argument(
        "Dijkstra algorithm can't work with negative path");
  if (graph.size() < vertex1 || graph.size() < vertex2 || vertex1 < 1 ||
      vertex2 < 1)
    throw std::out_of_range("out of range");
  unsigned length = 0;
  if (vertex1 != vertex2) {
    std::vector<int> shortest(graph.size(), INT_MAX);
    std::vector<bool> visited(graph.size(), false);
    int temp, minindex, min;
    shortest[vertex1 - 1] = 0U;
    const int size = graph.size();
    do {
      minindex = INT_MAX;
      min = INT_MAX;
      for (int i = 0; i < size; ++i) {
        if (!visited[i] && (shortest[i] < min)) {
          min = shortest[i];
          minindex = i;
        }
      }
      if (minindex != INT_MAX) {
        for (int i = 0; i < size; ++i) {
          if (graph.matrix()[minindex][i] > 0) {
            temp = min + graph.matrix()[minindex][i];
            if (temp < shortest[i]) {
              shortest[i] = temp;
            }
          }
        }
        visited[minindex] = true;
      }
    } while (minindex < INT_MAX);
    length = shortest[vertex2 - 1];
  }
  return length;
}

auto GraphAlgorithms::getShortestPathsBetweenAllVertices(Graph &graph)
    -> s21::Matrix<int> {
  if (graph.empty()) throw std::invalid_argument("graph is empty");
  s21::Matrix<int> matrix = graph.matrix();
  const int size = graph.size();
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      if (i != j && matrix[i][j] == 0) {
        matrix[i][j] = INT_MAX;
      }
    }
  }
  for (int k = 0; k < size; k++) {
    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
        if (matrix[i][k] != INT_MAX && matrix[k][j] != INT_MAX) {
          matrix[i][j] = std::min(matrix[i][j], matrix[i][k] + matrix[k][j]);
        }
      }
    }
  }
  return matrix;
}
