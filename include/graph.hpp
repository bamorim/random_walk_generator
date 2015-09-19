#include<vector>
#include<stdint.h>
#pragma once

class Graph {
  private:
    std::vector<std::vector<uint_fast32_t>> adjacencyVector;
    uint_fast32_t size_cache = 0;
  public: 
    uint_fast32_t order();
    uint_fast32_t size();
    void add_vertex();
    void add_edge(uint_fast32_t, uint_fast32_t);
    std::vector<uint_fast32_t> neighbors_of(uint_fast32_t);
};
