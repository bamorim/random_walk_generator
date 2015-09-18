#include<vector>
#pragma once

class Graph {
  private:
    std::vector<std::vector<long int>> adjacencyVector;
    long int size_cache = 0;
  public: 
    long int order();
    long int size();
    void addVertex();
    void addEdge(long int, long int);
};
