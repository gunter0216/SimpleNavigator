#include "randominator.h"
#include "s21_graph_algorithms.h"
#include "tsm_helper.h"
auto GraphAlgorithms::solveTsmAnnealing(Graph &graph) -> TsmResult {
  if (graph.empty()) throw std::invalid_argument("graph is empty");
  TsmResult result = TsmHelper::GenerateRandPath(graph), tmp = result;
  Randominator rnd;
  double temperature = 500., temp_step = 0.85;
  while (temperature > 0.1) {
    for (int i = 0; i < 200; ++i) {
      std::swap(tmp.vertices[rnd.RandItn(0, tmp.vertices.size() - 1)],
                tmp.vertices[rnd.RandItn(0, tmp.vertices.size() - 1)]);
      TsmHelper::CountDistance(tmp, graph);
      if (result.distance > tmp.distance or
          (exp((result.distance - tmp.distance) / temperature * 100.)) >
              ((double)rnd.RandItn() / RAND_MAX) * 100.) {
        result = tmp;
      } else {
        tmp = result;
      }
    }
    temperature *= temp_step;
  }
  return result;
}