#include<random_walk_generator.hpp>
#include<random_walker.hpp>
#include<queue>
#include<algorithm>

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

  Graph run(std::mt19937 * mt, uint_fast32_t max_order, uint_fast32_t steps, uint_fast32_t initial_order){
    Graph graph(max_order);
    initialize_complete_graph(graph, initial_order);
    RandomWalker walker(mt, &graph);

    while(graph.order() < max_order){
      for(uint_fast32_t i = 0; i < steps; i++){
        walker.take_step();
      }
      graph.add_vertex();
      graph.add_edge(graph.order()-1, walker.location());
    }

    return graph;
  }

  struct VerticeDepth {
    uint_fast32_t vertice;
    uint_fast32_t depth;
  };

  RandomWalkGenerator::Statistics measure(std::mt19937 * mt, uint_fast32_t max_order, uint_fast32_t steps, uint_fast32_t initial_order){
    auto graph = run(mt, max_order, steps, initial_order);
    RandomWalkGenerator::Statistics statistics;

    // Run a BFS on the graph, ignoring the initial_order edges
    // Starting in each one of those
    std::vector<bool> explored(graph.order(),false);
    std::queue<VerticeDepth> queue;

    for(uint_fast32_t start = 0; start < initial_order; start++){
      queue.push({start, 0});
      explored[start] = true;
    }

    while(!queue.empty()){
      auto curr = queue.front();
      queue.pop();

      // Documentar melhor porque foi dificil de explicar
      if(curr.depth >= statistics.vertices_per_depth.size()){
        statistics.vertices_per_depth.push_back(1);
      } else {
        statistics.vertices_per_depth[curr.depth]++;
      }

      for(auto n : *graph.neighbors_of(curr.vertice)) {
        if(!explored[n]){
          queue.push({n, curr.depth+1});
          explored[n] = true;
        }
      }
    }

    statistics.degree_distribution = graph.degree_distribution();
    return statistics;
  }

  // TODO: Calculate the space requirements for the accumulate measurments
  RandomWalkGenerator::Statistics accumulate_measure(std::mt19937 * mt, uint_fast32_t runs, uint_fast32_t max_order, uint_fast32_t steps, uint_fast32_t initial_order){
    std::vector<RandomWalkGenerator::Statistics> measures;
    RandomWalkGenerator::Statistics statistics;
    measures.reserve(runs);

    // actually is the max degree + 1
    uint_fast32_t max_degree = 0;
    uint_fast32_t max_depth = 0;

    for(uint_fast32_t i = 0; i < runs; i++){
      measures.push_back(measure(mt, max_order, steps, initial_order));
      max_degree = std::max(measures[i].degree_distribution.size(), max_degree);
      max_depth = std::max(measures[i].vertices_per_depth.size(), max_depth);
    }

    statistics.degree_distribution = std::vector<uint_fast32_t>(max_degree,0);
    statistics.vertices_per_depth = std::vector<uint_fast32_t>(max_depth,0);

    for(auto m : measures){
      for(uint_fast32_t i = 0; i < m.degree_distribution.size(); i ++){
        statistics.degree_distribution[i] += m.degree_distribution[i];
      }
      for(uint_fast32_t j = 0; j < m.vertices_per_depth.size(); j ++){
        statistics.vertices_per_depth[j] += m.vertices_per_depth[j];
      }
    }

    return statistics;
  }
}
