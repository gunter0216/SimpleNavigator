#ifndef GRAPH_S21_TYPES_H_
#define GRAPH_S21_TYPES_H_

#include <vector>

#include "../containers/s21_queue.h"
#include "../containers/s21_stack.h"
#include "../matrix/matrix.h"

using que_t = s21::queue<int>;
using stk_t = s21::stack<int>;
using matr_t = s21::Matrix<int>;

struct TsmResult {
  std::vector<int> vertices;
  double distance = 0.;
  bool operator>(const TsmResult& o) const { return distance > o.distance; }
  bool operator<(const TsmResult& o) const { return distance < o.distance; }
  bool operator>=(const TsmResult& o) const { return distance >= o.distance; }
  bool operator<=(const TsmResult& o) const { return distance <= o.distance; }
  bool operator==(const TsmResult& o) const {
    return distance == o.distance && vertices == o.vertices;
  }
};

#endif  //  GRAPH_S21_TYPES_H_
