TEST(bfs, 1) {
  Graph graph;
  graph.loadGraphFromFile(kExampleGraph1);
  GraphAlgorithms ga;
  ga.getLeastSpanningTree(graph);
  que_t result = ga.breadthFirstSearch(graph, 1);
  que_t exp{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
  while (!result.empty()) {
    EXPECT_EQ(exp.peek(), result.peek());
    exp.pop();
    result.pop();
  }
}

TEST(dfs, 1) {
  Graph graph;
  graph.loadGraphFromFile(kExampleGraph2);
  GraphAlgorithms ga;
  ga.getLeastSpanningTree(graph);
  que_t result = ga.depthFirstSearch(graph, 4);
  que_t exp{4, 2, 1, 3, 6, 5};
  while (!result.empty()) {
    EXPECT_EQ(exp.peek(), result.peek());
    exp.pop();
    result.pop();
  }
}