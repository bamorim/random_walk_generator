#include<graph.hpp>

uint_fast32_t Graph::order() const{
  return adjacency_vector.size();
}

uint_fast32_t Graph::size() const{
  return size_cache;
}

void Graph::add_vertex(){
  std::vector<uint_fast32_t> vec(0);
  adjacency_vector.push_back(vec);
}

void Graph::add_edge(uint_fast32_t from, uint_fast32_t to) {
  // Todo: Add exceptions here when from and to are out of range
  size_cache++;
  adjacency_vector[from].push_back(to);
  
  // Maybe a check for undirected vs directed would fit nice here
  adjacency_vector[to].push_back(from);
}

const std::vector<uint_fast32_t>* Graph::neighbors_of(uint_fast32_t vertex) const{
  return &adjacency_vector[vertex];
}

uint_fast32_t Graph::max_degree() const{
  uint_fast32_t degree = 0;
  for(auto v : adjacency_vector) {
    if(v.size() > degree) {
      degree = v.size();
    }
  }
  return degree;
}

const std::vector<uint_fast32_t> Graph::degree_distribution() const{
  std::vector<uint_fast32_t> degree_dist(max_degree()+1,0);
  for(auto v : adjacency_vector) {
    degree_dist[v.size()]++;
  }
  return degree_dist;
}
