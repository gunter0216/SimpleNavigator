#ifndef SRC_VIEW_CONSOLEVIEW_H_
#define SRC_VIEW_CONSOLEVIEW_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../graph/s21_graph.h"
#include "../graph_algorithms/s21_graph_algorithms.h"
#include "iostream"
#include "string"

class ConsoleView {
 public:
  ConsoleView();
  ~ConsoleView() = default;

 private:
  Graph graph_;
  GraphAlgorithms graph_algorithms;
  int command_ = -1;
  bool stop_ = false;

  auto PrintHelp() -> void;
  auto Loop() -> void;
  auto Code1() -> void;
  auto Code2() -> void;
  auto Code3() -> void;
  auto Code4() -> void;
  auto Code5() -> void;
  auto Code6() -> void;
  auto Code7() -> void;
  auto Code8() -> void;
  auto Code8_algorithms(int n, int num) -> void;
};

#endif  // SRC_VIEW_CONSOLEVIEW_H_
