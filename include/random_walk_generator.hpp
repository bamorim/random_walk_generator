#include<graph.hpp>
#include<vector>
#pragma once

namespace RandomWalkGenerator {
  struct Statistics {
    std::vector<uint_fast32_t> degree_distribution;
    std::vector<uint_fast32_t> vertices_per_depth;
  };

  Graph run(uint_fast32_t seed, uint_fast32_t max_order, uint_fast32_t steps, uint_fast32_t initial_order);
  Statistics measure(uint_fast32_t seed, uint_fast32_t max_order, uint_fast32_t steps, uint_fast32_t initial_order);
  Statistics accumulate_measure(std::vector<uint_fast32_t> seeds, uint_fast32_t max_order, uint_fast32_t steps, uint_fast32_t initial_order);
}
