#include<graph.hpp>
#include<vector>
#include<random>
#pragma once

namespace RandomWalkGenerator {
  struct Statistics {
    std::vector<uint_fast32_t> degree_distribution;
    std::vector<uint_fast32_t> vertices_per_depth;
  };

  Graph run(std::mt19937 * mt, uint_fast32_t max_order, uint_fast32_t steps, uint_fast32_t initial_order, bool selfloop);
  Statistics measure(std::mt19937 * mt, uint_fast32_t max_order, uint_fast32_t steps, uint_fast32_t initial_order, bool selfloop);
  Statistics accumulate_measure(std::mt19937 * mt, uint_fast32_t runs, uint_fast32_t max_order, uint_fast32_t steps, uint_fast32_t initial_order, bool selfloop);
}
