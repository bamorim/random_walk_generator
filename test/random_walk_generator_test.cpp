#include<catch.hpp>
#include<random_walk_generator.hpp>

#define TEST_SEED 0

Graph run(uint_fast32_t max_vertex, uint_fast32_t steps, uint_fast32_t initial_order){
  return RandomWalkGenerator::run(
      TEST_SEED, // seed for testing
      max_vertex,
      steps,
      initial_order
      );
};

Graph run_no_steps(uint_fast32_t initial_order){
  return run(
      1, // max vertex
      0, // steps
      initial_order
      );
};

TEST_CASE( "it should start with a complete graph" ){
  SECTION ( "for 1" ){
    Graph g = run_no_steps(1);
    REQUIRE(g.order() == 1);
    REQUIRE(g.size() == 0);
  }

  SECTION ( "for 2" ){
    Graph g = run_no_steps(2);
    REQUIRE(g.order() == 2);
    REQUIRE(g.size() == 1);
  }

  SECTION ( "for 10" ){
    Graph g = run_no_steps(10);
    REQUIRE(g.order() == 10);
    REQUIRE(g.size() == 45);
  }
}

TEST_CASE( "it should grow to max vertex" , "[special]"){
  Graph g = run(10, 1, 1);
  REQUIRE(g.order() == 10);
  REQUIRE(g.size() == 9);
}
