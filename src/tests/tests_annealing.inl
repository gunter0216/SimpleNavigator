TEST(annealing, 1) {
  Graph graph;
  graph.loadGraphFromFile(kExampleGraph2);
  GraphAlgorithms ga;
  std::set<double> dists;
  for (int i = 0; i < 20; ++i)
    dists.insert(ga.solveTsmAnnealing(graph).distance);
  EXPECT_TRUE(dists.count(46) or dists.count(40));
}

TEST(annealing, 2) {
  Graph graph;
  graph.loadGraphFromFile(kExampleGraph1);
  GraphAlgorithms ga;
  std::set<double> dists;
  for (int i = 0; i < 30; ++i)
    dists.insert(ga.solveTsmAnnealing(graph).distance);
  EXPECT_TRUE(*dists.begin() < 200);
}
