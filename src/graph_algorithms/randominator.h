#ifndef GRAPH_AGLORITHMS_RANDOMINATOR_H_
#define GRAPH_AGLORITHMS_RANDOMINATOR_H_

#include <random>

class Randominator {
 public:
  Randominator() {
    std::random_device rd;
    engine_ = std::default_random_engine(rd());
    distr_ = std::uniform_int_distribution<int>(0, RAND_MAX);
  }

  auto RandItn(int min = 0, int max = RAND_MAX) {
    return min + distr_(engine_) % max;
  }

 private:
  std::default_random_engine engine_;
  std::uniform_int_distribution<int> distr_;
};

#endif  //  GRAPH_AGLORITHMS_RANDOMINATOR_H_
