TEST(ant, 1) {
  Graph graph;
  graph.loadGraphFromFile(kExampleGraph2);
  GraphAlgorithms ga;
  std::set<double> dists;
  for (int i = 0; i < 20; ++i)
    dists.insert(ga.solveTravelingSalesmanProblem(graph).distance);
  EXPECT_TRUE(*dists.begin() < 50);
}

TEST(ant, 2) {
  Graph graph;
  graph.loadGraphFromFile(kExampleGraph1);
  GraphAlgorithms ga;
  std::set<double> dists;
  for (int i = 0; i < 30; ++i)
    dists.insert(ga.solveTravelingSalesmanProblem(graph).distance);
  EXPECT_TRUE(*dists.begin() < 255);
}