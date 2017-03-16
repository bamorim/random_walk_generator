#include<random_walk_generator.hpp>
#include<random_walker.hpp>
#include<queue>
#include<algorithm>

namespace RandomWalkGenerator {
  void initialize_complete_graph(Graph& graph, InitialState initial_state){
    uint_fast32_t i,j;
    for(i = 0; i < initial_state.order; i++){
      graph.add_vertex();
    }

    for(i = 0; i < initial_state.order; i++){
      if(initial_state.selfloop){
        graph.add_edge(i,i);
      }
      for(j = i+1; j < initial_state.order; j++){
        graph.add_edge(i,j);
      }
    }
  }

  StepFunction steps_const(uint_fast32_t s){
    return [s](auto n){
      return s;
    };
  }

  std::uniform_real_distribution<> dist(0,1);

  StepFunction steps_prob(std::mt19937 * mt, double p){
    return [mt, p](auto n){
      if(dist(*mt) > p){
        return 2;
      }
      return 1;
    };
  }

  StepFunction steps_log(double a, double b){
    return [a,b](auto n){
      return floor(b*log(n)/log(a));
    };
  }

  StepFunction steps_pow(double a, double b){
    return [a,b](auto n){
      return floor(b*pow(n,a));
    };
  }

  StepFunction steps_exp(double a, double b){
    return [a,b](auto n){
      return floor(b*pow(a,n));
    };
  }

  Graph run(std::mt19937 * mt, InitialState initial_state, StepFunction steps, uint_fast32_t max_order){
    Graph graph(max_order);
    initialize_complete_graph(graph, initial_state);
    RandomWalker walker(mt, &graph);

    while(graph.order() < max_order){
      for(uint_fast32_t i = 0; i < steps(graph.order()); i++){
        walker.take_step();
      }
      graph.add_vertex();
      graph.add_edge(graph.order()-1, walker.location());
    }

    return graph;
  }

  RandomWalkGenerator::Statistics measure(Graph& graph,uint_fast32_t initial_order){
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

  void sum_list_to(std::vector<uint_fast32_t>& from, std::vector<uint_fast32_t>& to) {
    for(uint_fast32_t i = 0; i < from.size(); i ++){
      if(to.size() > i) {
        to[i] += from[i];
      } else {
        to.push_back(from[i]);
      }
    }
  }

  // TODO: Calculate the space requirements for the accumulate measurments
  RandomWalkGenerator::Statistics acc_run_and_measure(std::mt19937 * mt, InitialState initial_state, StepFunction steps, uint_fast32_t max_order, uint_fast32_t runs){
    RandomWalkGenerator::Statistics measurement;
    RandomWalkGenerator::Statistics statistics;

    for(uint_fast32_t i = 0; i < runs; i++){
      Graph graph = run(mt, initial_state, steps, max_order);
      measurement = measure(graph, initial_state.order);
      sum_list_to(measurement.degree_distribution, statistics.degree_distribution);
      sum_list_to(measurement.vertices_per_depth, statistics.vertices_per_depth);
    }

    return statistics;
  }
}
