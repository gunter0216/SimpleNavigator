#ifndef A2_GENETIC_H
#define A2_GENETIC_H
#include <typeinfo>
#include <vector>

#include "../graph/s21_types.h"
#include "randominator.h"
#include "s21_graph_algorithms.h"
#include "tsm_helper.h"

class GeneticAlgorithm {
 public:
  GeneticAlgorithm(Graph &graph) : graph_(graph){};
  ~GeneticAlgorithm() = default;
  auto SolveTSM() -> TsmResult;

 private:
  const int kMaxPopulation = 30;
  auto GenerateChromosomes_(int n) -> void;
  auto Mutation_(TsmResult[2]) -> void;
  auto ChooseParents() -> std::pair<std::set<TsmResult>::iterator,
                                    std::set<TsmResult>::iterator>;
  auto Crossing_() -> void;

  Graph &graph_;
  std::multiset<TsmResult> population_;
  Randominator rd_;
  int mutation_perc_ = 90;
};

#endif  // A2_GENETIC_H
