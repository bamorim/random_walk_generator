#include<graph.hpp>

long int Graph::order(){
  return adjacencyVector.size();
}

long int Graph::size(){
  return size_cache;
}

void Graph::addVertex(){
  std::vector<long int> vec(0);
  adjacencyVector.push_back(vec);
}

void Graph::addEdge(long int from, long int to){
  // Todo: Add exceptions here when from and to are out of range
  size_cache++;
  adjacencyVector[from].push_back(to);
}
