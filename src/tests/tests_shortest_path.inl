TEST(getShortestPathBetweenVertices, find_path) {
  Graph graph;
  graph.loadGraphFromFile(kExampleGraph0);
  GraphAlgorithms ga;
  EXPECT_EQ(ga.getShortestPathBetweenVertices(graph, 1, 4), 66);
  EXPECT_EQ(ga.getShortestPathBetweenVertices(graph, 1, 11), 62);
  EXPECT_EQ(ga.getShortestPathBetweenVertices(graph, 18, 9), 136);
  EXPECT_EQ(ga.getShortestPathBetweenVertices(graph, 18, 9),
            ga.getShortestPathBetweenVertices(graph, 9, 18));
}

TEST(getShortestPathBetweenVertices, throw) {
  Graph graph;
  GraphAlgorithms ga;
  EXPECT_ANY_THROW(ga.getShortestPathBetweenVertices(graph, 1, 2));
  graph.loadGraphFromFile(kExampleGraph2);
  EXPECT_ANY_THROW(ga.getShortestPathBetweenVertices(graph, 18, 9));
  EXPECT_ANY_THROW(ga.getShortestPathBetweenVertices(graph, 1, 99));
  EXPECT_ANY_THROW(ga.getShortestPathBetweenVertices(graph, 0, 9));
  EXPECT_ANY_THROW(ga.getShortestPathBetweenVertices(graph, -1, 1));
}

TEST(getShortestPathsBetweenAllVertices, find_paths) {
  Graph graph;
  Graph graph1;
  GraphAlgorithms ga;
  graph.loadGraphFromFile(kExampleGraph0);
  graph1.loadGraphFromFile(kExampleGraph0);
  auto path_matr = ga.getShortestPathsBetweenAllVertices(graph);
  for (int i = 0; i < path_matr.getRows(); ++i)
    for (int j = 0; j < path_matr.getCols(); ++j)
      EXPECT_EQ(path_matr(i, j),
                ga.getShortestPathBetweenVertices(graph, i + 1, j + 1));
  EXPECT_TRUE(graph == graph1);
}

TEST(getShortestPathsBetweenAllVertices, throw) {
  Graph graph;
  GraphAlgorithms ga;
  EXPECT_ANY_THROW(ga.getShortestPathBetweenVertices(graph, 1, 2));
  graph.loadGraphFromFile(kExampleGraph2);
  EXPECT_ANY_THROW(ga.getShortestPathBetweenVertices(graph, 18, 9));
  EXPECT_ANY_THROW(ga.getShortestPathBetweenVertices(graph, 1, 99));
  EXPECT_ANY_THROW(ga.getShortestPathBetweenVertices(graph, 0, 9));
  EXPECT_ANY_THROW(ga.getShortestPathBetweenVertices(graph, -1, 1));
}
