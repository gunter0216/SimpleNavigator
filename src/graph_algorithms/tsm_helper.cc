#include "tsm_helper.h"

#include <list>

#include "randominator.h"

auto TsmHelper::CountDistance(TsmResult& way, Graph& graph) -> double {
  way.distance = 0.;
  for (auto i = way.vertices.begin() + 1; i < way.vertices.end(); ++i)
    way.distance += (graph.distBetween(*(i - 1), (*i)) == 0)
                        ? INFINITY
                        : (double)graph.distBetween(*(i - 1), (*i));
  return way.distance;
}

auto TsmHelper::GenerateRandPath(Graph& graph) -> TsmResult {
  TsmResult path{{}, 0.};
  Randominator rnd;
  path.vertices.reserve(graph.size());
  path.vertices.push_back(abs(rnd.RandItn(1, graph.size())));
  for (int i = 0; i < graph.size() - 1; ++i)
    path.vertices.push_back(1 + path.vertices.back() % graph.size());
  CountDistance(path, graph);
  return path;
}

auto TsmHelper::GenerateRandPathPlus(Graph& graph) -> TsmResult {
  std::set<int> tmp_list;
  for (int i = 1; i <= graph.size(); ++i) tmp_list.insert(i);
  TsmResult path{{}, 0.};
  path.vertices.reserve(graph.size());
  int rnd = Randominator().RandItn(99999, 1999999999) >> 1;
  while (!tmp_list.empty()) {
    auto itr = tmp_list.begin();
    for (int i = (int)((tmp_list.size() ^ rnd) % tmp_list.size()); i > 0; --i)
      itr++;
    rnd ^= 88;
    path.vertices.push_back(*itr);
    tmp_list.erase(itr);
  }
  CountDistance(path, graph);
  return path;
}
