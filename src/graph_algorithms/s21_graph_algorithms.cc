#include "s21_graph_algorithms.h"

#include "genetic.h"
#include "salesman_problem_ant.h"

GraphAlgorithms::~GraphAlgorithms() {
  delete DfsData.solution;
  delete DfsData.graph;
}

auto GraphAlgorithms::solveTsmGenetic(Graph &graph) -> TsmResult {
  if (graph.empty()) throw std::invalid_argument("graph is empty");
  GeneticAlgorithm gag(graph);
  return gag.SolveTSM();
}

auto GraphAlgorithms::solveTravelingSalesmanProblem(Graph &graph) -> TsmResult {
  if (graph.empty()) throw std::invalid_argument("graph is empty");
  AntAlgorithm algorithm;
  return algorithm.solveTravelingSalesmanProblem(graph);
}
