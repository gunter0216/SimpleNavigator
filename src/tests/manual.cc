#include <iostream>
#include <random>

#include "../graph/s21_graph.h"
#include "../graph_algorithms/randominator.h"
#include "../graph_algorithms/s21_graph_algorithms.h"

template <typename T>
void showVector(std::vector<T> &v);

template <typename T>
void showQueue(s21::queue<T> &q);

int main() {
  using std::cout;
  using std::endl;
  Graph gr;
  GraphAlgorithms ga;
  gr.loadGraphFromFile(
      "/Volumes/Kingston/projects/algorithm/a2/src/tests/example.graph");
  //  gr.loadGraphFromFile("/Volumes/Kingston/projects/algorithm/a2/src/tests/ex1.graph");
  //    gr.loadGraphFromFile("/Volumes/Kingston/review/a2/jmadie/src/files/graph1.txt");
  //    gr.loadGraphFromFile(
  //    "/Volumes/Kingston/review/a2/cshara/src/samples/test/find_10x10.graph");
  gr.exportGraphToDot("/Volumes/Kingston/projects/algorithm/a2/src/ex1.dot");

  auto tsm_ant = ga.solveTravelingSalesmanProblem(gr);
  cout << "ant\ndist: " << tsm_ant.distance << "\npath:\n";
  showVector(tsm_ant.vertices);
  auto annnealing = ga.solveTsmAnnealing(gr);
  cout << "annnealing\ndist: " << annnealing.distance << "\npath:\n";
  showVector(annnealing.vertices);

  auto genetic = ga.solveTsmGenetic(gr);
  cout << "genetic\ndist: " << genetic.distance << "\npath:\n";
  showVector(genetic.vertices);

  //    std::list<int>list{1,2,3,4,5,6};
  //    auto itr = ++list.begin();
  //    itr++;
  //    list.erase(itr);
  //    for (auto i:list)cout<<i<< ' ';
  //    cout << endl;
  //    itr++;
  //    cout << *itr << endl;
  //    for (int i = 0; i < 10000; ++i) {
  //      auto a = TsmHelper::GenerateRandPathPlus(gr).vertices;
  //      std::set<int> st{a.begin(), a.end()};
  //      if (a.size() != gr.size() or st.size() != gr.size()) showVector(a);
  //    }
  return 0;
}

template <typename T>
void showVector(std::vector<T> &v) {
  std::cout << "size: " << v.size() << "\ndata: ";
  for (auto i : v) {
    std::cout << i << ' ';
  }
  std::cout << '\n';
}

template <typename T>
void showQueue(s21::queue<T> &q) {
  std::cout << "size: " << q.size() << "\ndata: ";
  for (auto i = &q.front(); i <= &q.back(); ++i) std::cout << *i << ' ';
  std::cout << '\n';
}