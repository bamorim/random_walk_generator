#include<random_walk_generator.hpp>
#include<random_walker.hpp>

namespace RandomWalkGenerator {
  void initialize_complete_graph(Graph& graph, uint_fast32_t order){
    uint_fast32_t i,j;
    for(i = 0; i < order; i++){
      graph.add_vertex();
    }

    for(i = 0; i < order; i++){
      for(j = i+1; j < order; j++){
        graph.add_edge(i,j);
      }
    }
  }

  Graph run(uint_fast32_t seed, uint_fast32_t max_order, uint_fast32_t steps, uint_fast32_t initial_order){
    Graph graph;
    initialize_complete_graph(graph, initial_order);
    RandomWalker walker(seed, &graph);

    while(graph.order() < max_order){
      for(uint_fast32_t i = 0; i < steps; i++){
        walker.take_step();
      }
      graph.add_vertex();
      graph.add_edge(graph.order()-1, walker.location());
    }

    return graph;
  }
}
