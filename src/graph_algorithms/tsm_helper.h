#ifndef GRAPH_AGLORITHMS_TSM_HELPER_H_
#define GRAPH_AGLORITHMS_TSM_HELPER_H_

#include "../graph/s21_graph.h"
#include "../graph/s21_types.h"
class TsmHelper {
 public:
  static auto CountDistance(TsmResult& way, Graph& graph) -> double;
  static auto GenerateRandPath(Graph& graph) -> TsmResult;
  static auto GenerateRandPathPlus(Graph& graph) -> TsmResult;
};

#endif  //  GRAPH_AGLORITHMS_TSM_HELPER_H_
