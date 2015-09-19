#include<graph.hpp>

uint_fast32_t Graph::order(){
  return adjacencyVector.size();
}

uint_fast32_t Graph::size(){
  return size_cache;
}

void Graph::add_vertex(){
  std::vector<uint_fast32_t> vec(0);
  adjacencyVector.push_back(vec);
}

void Graph::add_edge(uint_fast32_t from, uint_fast32_t to){
  // Todo: Add exceptions here when from and to are out of range
  size_cache++;
  adjacencyVector[from].push_back(to);
  
  // Maybe a check for undirected vs directed would fit nice here
  adjacencyVector[to].push_back(from);
}

std::vector<uint_fast32_t> Graph::neighbors_of(uint_fast32_t vertex){
  return adjacencyVector[vertex];
}
