#include<vector>
#include<stdint.h>
#pragma once

class Graph {
  private:
    std::vector<std::vector<uint_fast32_t>> adjacency_vector;
    uint_fast32_t size_cache = 0;
  public: 
    Graph(){};
    Graph(uint_fast32_t prealloc){adjacency_vector.reserve(prealloc);}
    uint_fast32_t order();
    uint_fast32_t size();
    uint_fast32_t max_degree();
    void add_vertex();
    void add_edge(uint_fast32_t, uint_fast32_t);
    std::vector<uint_fast32_t> neighbors_of(uint_fast32_t);
    std::vector<uint_fast32_t> degree_distribution();
};
