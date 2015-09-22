#include<random_walker.hpp>
RandomWalker::RandomWalker(uint_fast32_t seed, Graph * g) {
  m_location = 0;
  graph_ptr = g;
  twister = std::mt19937(seed);
}

uint_fast32_t RandomWalker::take_step() {
  auto neighbors = graph_ptr->neighbors_of(m_location);

  if(neighbors->size() == 0)
    return m_location;

  std::uniform_int_distribution<uint_fast32_t> dist(0,neighbors->size()-1);

  m_location = (*neighbors)[dist(twister)];
  return m_location;
}
