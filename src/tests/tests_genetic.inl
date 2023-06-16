TEST(genetic, 1) {
  Graph graph;
  graph.loadGraphFromFile(kExampleGraph2);
  GraphAlgorithms ga;
  std::set<double> dists;
  for (int i = 0; i < 30; ++i)
    dists.insert(ga.solveTsmGenetic(graph).distance);
  EXPECT_TRUE(*dists.begin() < 50);
}

TEST(genetic, 2) {
  Graph graph;
  graph.loadGraphFromFile(kExampleGraph1);
  GraphAlgorithms ga;
  std::set<double> dists;
  for (int i = 0; i < 40; ++i)
    dists.insert(ga.solveTsmGenetic(graph).distance);
  EXPECT_TRUE(*dists.begin() < 200);
}
