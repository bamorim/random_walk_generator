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
    uint_fast32_t order() const;
    uint_fast32_t size() const;
    uint_fast32_t max_degree() const;
    void add_vertex();
    void add_edge(uint_fast32_t, uint_fast32_t);
    const std::vector<uint_fast32_t>* neighbors_of(uint_fast32_t) const;
    std::vector<uint_fast32_t> degree_distribution() const;
};
