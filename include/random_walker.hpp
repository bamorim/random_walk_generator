#include<random>
#include<graph.hpp>
#pragma once

class RandomWalker {
  public:
    RandomWalker(std::mt19937 *mt, Graph* graph);
    uint_fast32_t location(){ return m_location; }
    uint_fast32_t take_step();
  private:
    std::mt19937 * twister;
    Graph * graph_ptr;
    uint_fast32_t m_location;
};
