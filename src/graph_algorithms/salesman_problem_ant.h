#ifndef SRC_GRAPH_SALESMAN_PROBLEM_ANT_H_
#define SRC_GRAPH_SALESMAN_PROBLEM_ANT_H_

#include <cmath>
#include <vector>

#include "../graph/s21_graph.h"
#include "../graph/s21_types.h"
#include "randominator.h"

class AntAlgorithm {
 public:
  AntAlgorithm() = default;
  ~AntAlgorithm() = default;
  AntAlgorithm(const AntAlgorithm &) = delete;
  AntAlgorithm(AntAlgorithm &&) = delete;
  auto operator=(const AntAlgorithm &) = delete;
  auto operator=(AntAlgorithm &&) = delete;
  auto solveTravelingSalesmanProblem(Graph &graph) -> TsmResult;

 private:
  struct AntType {
    int curVert, nextVert, pathIndex;
    std::vector<int> tabu;
    std::vector<int> path;
    double tourLength;
  };
  const double kAlpha = 1.0;
  const double kBeta = 5.0;
  const double kRho = 0.5;
  const int kQval = 100;
  const int kMaxTours = 20;
  int max_time_{0};
  double init_pher_{0.0};

  auto init(Graph &graph) -> void;
  auto restartAnts() -> void;
  auto antProduct(int from, int to) -> double;
  auto selectNextVert(int ant) -> int;
  auto simulateAnts() -> int;
  auto updateTrails() -> void;

  int count_vert_{0};
  int count_ants_{0};
  std::vector<AntType> ants_;
  s21::Matrix<int> dist_;
  s21::Matrix<double> phero_;
  double best_{};
  int bestIndex_{};
  Randominator rd_;
};

#endif  // SRC_GRAPH_SALESMAN_PROBLEM_ANT_H_
