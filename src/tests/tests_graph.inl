TEST(distBetween, 1) {
  Graph graph;
  graph.loadGraphFromFile(kExampleGraph1);
  EXPECT_EQ(graph.distBetween(2, 1), graph.distBetween(1, 2));
  EXPECT_EQ(graph.distBetween(4, 7), graph.distBetween(7, 4));
  EXPECT_EQ(graph.distBetween(11, 1), graph.distBetween(1, 11));
  EXPECT_EQ(graph.distBetween(6, 9), graph.distBetween(9, 6));
}

TEST(distBetween, auto) {
  Graph graph;
  graph.loadGraphFromFile(kExampleGraph1);
  s21::Matrix<int> matrix(kExampleGraph1);
  for (int i = 0; i < matrix.getCols(); ++i)
    for (int j = 0; j < matrix.getCols(); ++j)
      EXPECT_EQ(matrix(i, j), graph.distBetween(i + 1, j + 1));
}

TEST(distBetween, throw) {
  Graph graph;
  graph.loadGraphFromFile(kExampleGraph1);
  EXPECT_ANY_THROW(graph.distBetween(2, 12));
  EXPECT_ANY_THROW(graph.distBetween(0, 0));
  EXPECT_ANY_THROW(graph.distBetween(12, 12));
}

TEST(allConnections, 1) {
  Graph graph;
  graph.loadGraphFromFile(kExampleGraph1);
  EXPECT_ANY_THROW(graph.allConnections(12));
  EXPECT_NO_THROW(graph.allConnections(1));
}

TEST(operator, eq) {
  Graph g1, g2;
  g1.loadGraphFromFile(kExampleGraph1);
  EXPECT_FALSE(g1 == g2);
  EXPECT_FALSE(g2 == g1);
  g2.loadGraphFromFile(kExampleGraph1);
  EXPECT_TRUE(g1 == g2);
  EXPECT_TRUE(g2 == g1);
  EXPECT_TRUE(g1 == g1);
  EXPECT_TRUE(g2 == g2);
}

TEST(operator, copy) {
  Graph g1, g2;
  g1.loadGraphFromFile(kExampleGraph1);
  g2 = g1;
  EXPECT_TRUE(g1 == g2);
}

TEST(operator, move) {
  Graph g1, g2, g3;
  g1.loadGraphFromFile(kExampleGraph1);
  g2 = std::move(g1);
  EXPECT_FALSE(g1 == g2);
  EXPECT_FALSE(g2 == g1);
  EXPECT_TRUE(g1 == g3);
}

TEST(constructor, copy) {
  Graph g1;
  g1.loadGraphFromFile(kExampleGraph1);
  Graph g2(g1);
  EXPECT_TRUE(g1 == g2);
}

TEST(constructor, move) {
  Graph g1, g3;
  g1.loadGraphFromFile(kExampleGraph1);
  Graph g2(std::move(g1));
  EXPECT_FALSE(g1 == g2);
  EXPECT_FALSE(g2 == g1);
  EXPECT_TRUE(g1 == g3);
}

TEST(export, 1) {
  Graph graph;
  graph.loadGraphFromFile(kExampleGraph2);
  EXPECT_ANY_THROW(graph.exportGraphToDot(""));
}

TEST(export, 2) {
  Graph graph;
  graph.loadGraphFromFile(kExampleGraph2);
  graph.loadGraphFromFile(kExampleGraph2);
  EXPECT_NO_THROW(graph.exportGraphToDot("ex.dot"));
  system("rm ex.dot");
}
