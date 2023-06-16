#ifndef A2_SRC_TESTS_TESTS_H_
#define A2_SRC_TESTS_TESTS_H_
#include <gtest/gtest.h>

#include <set>

#include "../graph/s21_graph.h"
#include "../graph_algorithms/s21_graph_algorithms.h"

const std::string kExampleGraph0 = "./tests/ex1.graph";
const std::string kExampleGraph1 = "./tests/example.graph";
const std::string kExampleGraph2 = "./tests/example2.graph";
#include "tests_annealing.inl"
#include "tests_ant.inl"
#include "tests_genetic.inl"
#include "tests_graph.inl"
#include "tests_search.inl"
#include "tests_shortest_path.inl"

#endif  // A2_SRC_TESTS_TESTS_H_
