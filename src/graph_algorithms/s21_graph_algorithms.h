#ifndef SRC_GRAPH_S21_GRAPH_ALGORITHMS_H_
#define SRC_GRAPH_S21_GRAPH_ALGORITHMS_H_

#include <algorithm>
#include <climits>
#include <list>
#include <map>
#include <vector>

#include "../graph/s21_graph.h"
#include "../graph/s21_types.h"
#include "genetic.h"
#include "salesman_problem_ant.h"
#include "tsm_helper.h"

class GraphAlgorithms {
 public:
  GraphAlgorithms() = default;
  ~GraphAlgorithms();
  GraphAlgorithms(const GraphAlgorithms &) = delete;
  GraphAlgorithms(GraphAlgorithms &&) = delete;
  auto operator=(const GraphAlgorithms &) = delete;
  auto operator=(GraphAlgorithms &&) = delete;

  auto depthFirstSearch(Graph &graph, int startVertex) -> que_t;
  auto breadthFirstSearch(Graph &graph, int startVertex) -> que_t;
  auto getShortestPathBetweenVertices(Graph &graph, int vertex1, int vertex2)
      -> unsigned;
  auto getShortestPathsBetweenAllVertices(Graph &graph) -> s21::Matrix<int>;
  auto getLeastSpanningTree(Graph &graph) -> Graph;
  auto solveTravelingSalesmanProblem(Graph &graph) -> TsmResult;
  auto solveTsmAnnealing(Graph &graph) -> TsmResult;
  auto solveTsmGenetic(Graph &graph) -> TsmResult;

 private:
  struct {
    std::vector<bool> visited;
    Graph *graph = nullptr;
    que_t *solution = nullptr;
  } DfsData;

  void dfs_(int n);
};

#endif  // SRC_GRAPH_S21_GRAPH_ALGORITHMS_H_
