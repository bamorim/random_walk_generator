#include<random>
#include<vector>
#include<functional>
#include<graph.hpp>
#pragma once

namespace RandomWalkGenerator {
  struct Statistics {
    std::vector<uint_fast32_t> degree_distribution;
    std::vector<uint_fast32_t> vertices_per_depth;
  };

  void sum_list_to(std::vector<uint_fast32_t>& from, std::vector<uint_fast32_t>& to);
  Graph run(std::mt19937 * mt, uint_fast32_t max_order, uint_fast32_t steps, uint_fast32_t initial_order, bool selfloop);
  Graph run_one_or_two(std::mt19937 * mt, uint_fast32_t max_order, double p, uint_fast32_t initial_order, bool selfloop);
  Statistics measure(Graph &, uint_fast32_t initial_order);
  Statistics accumulate_measure(std::function<Graph(void)> runner, uint_fast32_t runs,uint_fast32_t initial_order);
}
