#include "salesman_problem_ant.h"

auto AntAlgorithm::solveTravelingSalesmanProblem(Graph &graph) -> TsmResult {
  if (graph.empty()) throw std::out_of_range("graph is empty");
  TsmResult result;
  result.distance = 0;
  result.vertices = std::vector<int>{};

  int curTime = 0;
  init(graph);
  while (curTime++ < max_time_) {
    if (simulateAnts() == 0) {
      updateTrails();
      if (curTime != max_time_) restartAnts();
    }
  }

  result.distance = best_;
  for (int i = 0; i < count_vert_; ++i) {
    result.vertices.push_back(ants_[bestIndex_].path[i] + 1);
  }

  return result;
}

void AntAlgorithm::init(Graph &graph) {
  dist_ = graph.matrix();

  for (int i = 0; i < dist_.size(); ++i) {
    for (int j = 0; j < dist_.size(); ++j) {
      if (i == j || dist_[i][j] == 0) dist_[i][j] = INT_MAX;
    }
  }
  count_vert_ = dist_.size();
  count_ants_ = dist_.size();
  max_time_ = count_vert_ * kMaxTours;
  init_pher_ = 1.0 / count_vert_;

  if (!ants_.empty()) ants_.clear();
  ants_ = std::vector<AntType>(count_ants_);
  for (size_t i = 0; i < (size_t)count_ants_; ++i) {
    ants_[i].tabu = std::vector<int>(count_vert_);
    ants_[i].path = std::vector<int>(count_vert_);
  }
  phero_ = s21::Matrix<double>{count_vert_, count_vert_};
  best_ = INFINITY;
  bestIndex_ = 0;

  for (int i = 0; i < count_vert_; ++i) {
    for (int j = 0; j < count_vert_; ++j) {
      phero_[i][j] = init_pher_;
    }
  }
  int to = 0;
  for (int i = 0; i < count_ants_; ++i) {
    if (to == count_vert_) to = 0;
    ants_[i].curVert = to++;
    for (int j = 0; j < count_vert_; ++j) {
      ants_[i].tabu[j] = 0;
      ants_[i].path[j] = -1;
    }
    ants_[i].pathIndex = 1;
    ants_[i].path[0] = ants_[i].curVert;
    ants_[i].nextVert = -1;
    ants_[i].tourLength = 0;
    ants_[i].tabu[ants_[i].curVert] = 1;
  }
}

int AntAlgorithm::simulateAnts() {
  int moving = 0;
  for (int i = 0; i < count_ants_; ++i) {
    if (ants_[i].pathIndex < count_vert_) {
      ants_[i].nextVert = selectNextVert(i);
      ants_[i].tabu[ants_[i].nextVert] = 1;
      ants_[i].path[ants_[i].pathIndex++] = ants_[i].nextVert;
      ants_[i].tourLength += dist_[ants_[i].curVert][ants_[i].nextVert];

      if (ants_[i].pathIndex == count_vert_) {
        ants_[i].tourLength +=
            dist_[ants_[i].path[count_vert_ - 1]][ants_[i].path[0]];
      }

      ants_[i].curVert = ants_[i].nextVert;
      ++moving;
    }
  }

  return moving;
}

void AntAlgorithm::updateTrails() {
  for (int i = 0; i < count_vert_; ++i) {
    for (int j = 0; j < count_vert_; ++j) {
      if (i != j) {
        phero_[i][j] *= (1.0 - kRho);
        if (phero_[i][j] < 0.0) {
          phero_[i][j] = init_pher_;
        }
      }
    }
  }
  for (int i = 0; i < count_ants_; ++i) {
    for (int j = 0; j < count_vert_; ++j) {
      int from, to;
      if (j < count_vert_ - 1) {
        from = ants_[i].path[j];
        to = ants_[i].path[j + 1];
      } else {
        from = ants_[i].path[j];
        to = ants_[i].path[0];
      }
      phero_[from][to] += (kQval / ants_[i].tourLength);
      phero_[to][from] = phero_[from][to];
    }
  }
  for (int i = 0; i < count_vert_; ++i) {
    for (int j = 0; j < count_vert_; ++j) {
      phero_[i][j] *= kRho;
    }
  }
}

int AntAlgorithm::selectNextVert(int ant) {
  int from, i;
  double denom = 0.0;
  from = ants_[ant].curVert;
  for (i = 0; i < count_vert_; ++i) {
    if (ants_[ant].tabu[i] == 0) {
      denom += antProduct(from, i);
    }
  }
  bool stop = false;
  do {
    ++i;
    if (i >= count_vert_) i = 0;
    if (ants_[ant].tabu[i] == 0) {
      double p = antProduct(from, i) / denom;
      double x = ((double)rd_.RandItn() / RAND_MAX);
      if (x < p) {
        stop = true;
      }
    }
  } while (!stop);
  return i;
}

void AntAlgorithm::restartAnts() {
  int to = 0;
  for (int i = 0; i < count_ants_; ++i) {
    if (ants_[i].tourLength < best_ && ants_[i].tourLength < INT_MAX) {
      best_ = ants_[i].tourLength;
      bestIndex_ = i;
    }
    ants_[i].nextVert = -1;
    ants_[i].tourLength = 0.0;
    for (int j = 0; j < count_vert_; ++j) {
      ants_[i].tabu[j] = 0;
      ants_[i].path[j] = -1;
    }
    if (to == count_vert_) to = 0;
    ants_[i].curVert = to++;
    ants_[i].pathIndex = 1;
    ants_[i].path[0] = ants_[i].curVert;
    ants_[i].tabu[ants_[i].curVert] = 1;
  }
}

double AntAlgorithm::antProduct(int from, int to) {
  return (
      (pow(phero_[from][to], kAlpha) * pow((1.0 / dist_[from][to]), kBeta)));
}

// 1 0 2 5 4 3
// 2 1 3 6 5 4
// 0 2 5 4 3 1