#ifndef SRC_GRAPH_S21_GRAPH_H_
#define SRC_GRAPH_S21_GRAPH_H_

#include <fstream>
#include <set>
#include <string>

#include "../matrix/matrix.h"
#include "s21_types.h"

class Graph {
 public:
  enum { kWeighted = 1u, kNegativeEdge = 2u };

  explicit Graph() = default;
  Graph(Graph &&o) noexcept;             // move
  Graph(const Graph &o);                 // copy
  Graph &operator=(Graph &&o) noexcept;  // move
  Graph &operator=(const Graph &o);      // copy
  bool operator==(const Graph &o);
  ~Graph();
  auto loadGraphFromFile(const std::string &filename) -> void;
  void setMatrix(matr_t &m);
  auto exportGraphToDot(const std::string &filename) -> void;
  auto distBetween(int a, int b) -> int;
  auto allConnections(int n) -> que_t;
  auto size() { return graph_matr_->getCols(); }
  auto info() { return graph_info_; }
  auto const &matrix() { return *graph_matr_; }
  auto empty() { return graph_matr_ == nullptr; }

 private:
  void RefreshGraphInfo_();

  matr_t *graph_matr_ = nullptr;
  unsigned char graph_info_ = 0;
};

#endif  // SRC_GRAPH_S21_GRAPH_H_
