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

  Graph run(uint_fast32_t seed, uint_fast32_t max_order, uint_fast32_t steps, uint_fast32_t initial_order){
    Graph graph(max_order);
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

  struct VerticeDepth {
    uint_fast32_t vertice;
    uint_fast32_t depth;
  };

  RandomWalkGenerator::Statistics measure(uint_fast32_t seed, uint_fast32_t max_order, uint_fast32_t steps, uint_fast32_t initial_order){
    auto graph = run(seed, max_order, steps, initial_order);
    RandomWalkGenerator::Statistics statistics;

    // Run a BFS on the graph, ignoring the initial_order edges
    // Starting in each one of those
    std::vector<bool> explored(graph.order(),false);
    std::queue<VerticeDepth> queue;

    for(uint_fast32_t start = 0; start < initial_order; start++){

      queue.push({start, 0});
      explored[start] = true;
      while(!queue.empty()){
        auto curr = queue.back();
        queue.pop();

        if(curr.depth >= statistics.vertices_per_depth.size()){
          statistics.vertices_per_depth.push_back(1);
        } else {
          statistics.vertices_per_depth[curr.depth]++;
        }

        for(auto n : *graph.neighbors_of(curr.vertice)) {
          // Ignore connections with the initial_order vertices
          if(curr.vertice >= initial_order || n >= initial_order){
            if(!explored[n]){
              queue.push({n, curr.depth+1});
              explored[n] = true;
            }
          }
        }
      }
    }

    statistics.degree_distribution = graph.degree_distribution();
    return statistics;
  }

  RandomWalkGenerator::Statistics accumulate_measure(std::vector<uint_fast32_t> seeds, uint_fast32_t max_order, uint_fast32_t steps, uint_fast32_t initial_order){
    std::vector<RandomWalkGenerator::Statistics> measures;
    RandomWalkGenerator::Statistics statistics;
    measures.reserve(seeds.size());
    uint_fast32_t max_degree = 0;
    uint_fast32_t max_depth = 0;

    for(auto seed : seeds){//uint_fast32_t i = 0; i < seeds.size(); i++){
      measures.push_back(measure(seed, max_order, steps, initial_order));
      max_degree = std::max(measures.back().degree_distribution.size(), max_degree);
      max_depth = std::max(measures.back().vertices_per_depth.size(), max_depth);
    }

    statistics.degree_distribution = std::vector<uint_fast32_t>(max_degree,0);
    statistics.vertices_per_depth = std::vector<uint_fast32_t>(max_depth,0);

    for(auto m : measures){
      for(uint_fast32_t j = 0; j < m.degree_distribution.size(); j ++){
        statistics.degree_distribution[j] += m.degree_distribution[j];
      }
      for(uint_fast32_t j = 0; j < m.vertices_per_depth.size(); j ++){
        statistics.vertices_per_depth[j] += m.vertices_per_depth[j];
      }
    }

    return statistics;
  }
}
