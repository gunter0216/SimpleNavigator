#include "genetic.h"

auto GeneticAlgorithm::SolveTSM() -> TsmResult {
  GenerateChromosomes_(kMaxPopulation);
  for (int i = 0; i < 500; ++i) {
    Crossing_();
    while ((int)population_.size() > kMaxPopulation)
      population_.erase(--population_.end());
  }
  return *population_.begin();
}

auto GeneticAlgorithm::GenerateChromosomes_(int n) -> void {
  for (int i = 0; i < n; ++i)
    population_.insert(TsmHelper::GenerateRandPathPlus(graph_));
}

auto GeneticAlgorithm::Crossing_() -> void {
  auto p = ChooseParents();
  std::pair<TsmResult, TsmResult> parents;
  parents.first = *p.first;
  parents.second = *p.second;
  const int wrap = rd_.RandItn(((graph_.size() > 3) ? 2 : 1),
                               graph_.size() - (graph_.size() > 3 ? 3 : 2));
  TsmResult child[2];
  for (int i = 0; i < 2; ++i) {
    child[i] = {std::vector<int>{parents.first.vertices.begin(),
                                 parents.first.vertices.begin() + wrap},
                0.};
    child[i].vertices.resize(parents.first.vertices.size());
    std::set<int> checked(child[i].vertices.begin(),
                          child[i].vertices.begin() + wrap);
    std::set<int> no_checked(parents.first.vertices.begin() + (wrap - 1),
                             parents.first.vertices.end());
    std::set<int> skips;
    std::list<int> gens(parents.first.vertices.begin(),
                        parents.first.vertices.end());
    for (int j = wrap - 1; j < (int)parents.first.vertices.size(); ++j) {
      if (no_checked.count(parents.second.vertices[j])) {
        child[i].vertices[j] = parents.second.vertices[j];
        no_checked.erase(no_checked.find(parents.second.vertices[j]));
      } else {
        skips.insert(j);
      }
    }
    auto itr = gens.begin();
    while (!no_checked.empty()) {
      if (!no_checked.count(*itr)) {
        no_checked.erase(*itr);
        gens.erase(itr);
      } else {
        no_checked.erase(*itr);
      }
      itr++;
    }
    for (auto j : skips) {
      child[i].vertices[j] = gens.front();
      gens.pop_front();
    }
    TsmHelper::CountDistance(child[i], graph_);
    if (!i) std::swap(parents.first, parents.second);
  }
  if (rd_.RandItn(0, 100) < mutation_perc_) Mutation_(child);
}

auto GeneticAlgorithm::ChooseParents()
    -> std::pair<std::set<TsmResult>::iterator, std::set<TsmResult>::iterator> {
  std::pair<std::set<TsmResult>::iterator, std::set<TsmResult>::iterator> res =
      {population_.begin(), population_.end()};
  for (int i = rd_.RandItn(0, (int)population_.size() >> 1); i; --i)
    res.first++;
  for (int i = rd_.RandItn(1, (int)population_.size() >> 1); i; --i)
    res.second--;
  if (res.first == res.second) {
    res.second--;
    res.first++;
  }
  return res;
}

auto GeneticAlgorithm::Mutation_(TsmResult* children) -> void {
  for (int i = 0; i < 2; ++i) {
    auto tmp = children[i];
    int a = rd_.RandItn(0, graph_.size() - 1);
    int b = rd_.RandItn(0, graph_.size() - 1);
    while (a == b) b = rd_.RandItn(0, graph_.size() - 1);
    std::swap(tmp.vertices[a], tmp.vertices[b]);
    if (tmp < children[i]) {
      population_.insert(tmp);
    } else {
      population_.insert(children[i]);
    }
  }
  if (mutation_perc_ > 20) mutation_perc_ -= rd_.RandItn(0, 1);
}
