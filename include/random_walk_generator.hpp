#include<random>
#include<vector>
#include<functional>
#include<graph.hpp>
#pragma once

namespace RandomWalkGenerator {
  typedef std::function<uint_fast32_t(uint_fast32_t)> StepFunction;

  struct InitialState {
  	uint_fast32_t order;
  	bool selfloop;
  };

  struct Statistics {
    std::vector<uint_fast32_t> degree_distribution;
    std::vector<uint_fast32_t> vertices_per_depth;
  };

  struct VerticeDepth {
    uint_fast32_t vertice;
    uint_fast32_t depth;
  };

  void sum_list_to(std::vector<uint_fast32_t>& from, std::vector<uint_fast32_t>& to);
  Graph run(std::mt19937 * mt, InitialState initial_state, StepFunction steps, uint_fast32_t max_order);
  Statistics measure(Graph &, uint_fast32_t initial_order);
  Statistics acc_run_and_measure(std::mt19937 * mt, InitialState initial_state, StepFunction steps, uint_fast32_t max_order, uint_fast32_t runs);
  StepFunction steps_const(uint_fast32_t s);
  StepFunction steps_prob(std::mt19937 * mt, double p);
  StepFunction steps_log(double a, double b);
  StepFunction steps_pow(double a, double b);
  StepFunction steps_exp(double a, double b);
}
