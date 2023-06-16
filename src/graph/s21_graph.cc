#include "s21_graph.h"

Graph::Graph(Graph &&o) noexcept {
  if (this != &o) {
    graph_matr_ = o.graph_matr_;
    graph_info_ = o.graph_info_;
    o.graph_matr_ = nullptr;
    o.graph_info_ = 0;
  }
}

Graph::Graph(const Graph &o) {
  if (this != &o) {
    graph_matr_ = new matr_t(*o.graph_matr_);
    graph_info_ = o.graph_info_;
  }
}

Graph::~Graph() {
  if (graph_matr_) delete graph_matr_;
}

Graph &Graph::operator=(Graph &&o) noexcept {
  if (this != &o) {
    this->graph_matr_ = o.graph_matr_;
    this->graph_info_ = o.graph_info_;
    o.graph_matr_ = nullptr;
    o.graph_info_ = 0;
  }
  return *this;
}

Graph &Graph::operator=(const Graph &o) {
  if (this != &o) {
    graph_info_ = o.graph_info_;
    delete this->graph_matr_;
    this->graph_matr_ = new matr_t(*o.graph_matr_);
  }
  return *this;
}

auto Graph::loadGraphFromFile(const std::string &filename) -> void {
  if (graph_matr_ != nullptr)
    delete graph_matr_;
  try {
    graph_matr_ = new matr_t(filename);
  } catch(...) {
    graph_matr_ = nullptr;
    throw std::invalid_argument("cat't open file");
  }
  RefreshGraphInfo_();
}

void Graph::setMatrix(matr_t &m) {
  if (m.getCols() != m.getRows())
    throw std::invalid_argument("The matrix isn't square");
  delete graph_matr_;
  graph_matr_ = new matr_t(m);
  RefreshGraphInfo_();
}

auto Graph::exportGraphToDot(const std::string &filename) -> void {
  if (filename.empty()) throw std::invalid_argument("Path is empty");
  std::ofstream file(filename);
  if (file.is_open()) {
    file << "graph {\n";
    for (int i = 0; i < graph_matr_->getCols(); ++i)
      for (int j = i + 1; j < graph_matr_->getCols(); ++j)
        if (graph_matr_->operator()(i, j)) {
          file << "    " << i + 1 << " -- " << j + 1;
          if (graph_info_ & kWeighted)
            file << " [label=" << graph_matr_->operator()(i, j) << "]";
          file << ";\n";
        }
    file << "}\n";
    file.close();
  }
}

auto Graph::distBetween(int a, int b) -> int {
  if (a > graph_matr_->getCols() or b > graph_matr_->getCols())
    throw std::out_of_range("distBetween" + std::to_string(a) + " " +
                            std::to_string(b));
  return graph_matr_->operator()(a - 1, b - 1);
}

auto Graph::allConnections(int n) -> que_t {
  if (n < 1 or n > graph_matr_->getCols())
    throw std::invalid_argument("Non existed vertex");
  n--;
  que_t connects;
  for (int i = 0; i < graph_matr_->getCols(); ++i)
    if (graph_matr_->operator()(i, n)) connects.push(i + 1);
  return connects;
}

void Graph::RefreshGraphInfo_() {
  graph_info_ = 0;
  for (int i = 0; i < graph_matr_->getCols(); ++i)
    for (int j = 0; j < graph_matr_->getRows(); ++j)
      if (graph_matr_->operator()(i, j) != 0 &&
          graph_matr_->operator()(i, j) != 1) {
        graph_info_ |= kWeighted;
        if (graph_matr_->operator()(i, j) < 0) {
          graph_info_ |= kNegativeEdge;
          return;
        }
      }
}

bool Graph::operator==(const Graph &o) {
  bool res = graph_matr_ == o.graph_matr_;
  if (!res and (graph_matr_ == nullptr or o.graph_matr_ == nullptr)) {
    res = false;
  } else if (!res) {
    res = (*graph_matr_ == *o.graph_matr_);
  }
  return res;
}
