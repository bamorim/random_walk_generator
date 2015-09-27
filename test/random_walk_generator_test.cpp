#include<catch.hpp>
#include<random_walk_generator.hpp>

#define TEST_SEED 0

Graph run(uint_fast32_t max_vertex, uint_fast32_t steps, uint_fast32_t initial_order){
  std::mt19937 mt(TEST_SEED);
  return RandomWalkGenerator::run(
      &mt, // seed for testing
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

TEST_CASE( "it should measure the depth correctly" , "[measure]"){
  std::mt19937 mt(TEST_SEED);
  SECTION ( "for max order equals initial order" ) {
    auto stats = RandomWalkGenerator::measure(
        &mt,
        3,
        1,
        3
        );
    REQUIRE(stats.vertices_per_depth[0] == 3);
    REQUIRE(stats.vertices_per_depth.size() == 1);
  }

  SECTION ( "some regression test" ){
    auto stats = RandomWalkGenerator::measure(
        &mt,
        10,
        2,
        3
        );
    REQUIRE(stats.vertices_per_depth[0] == 3);
    REQUIRE(stats.vertices_per_depth[1] == 7);
    REQUIRE(stats.vertices_per_depth.size() == 2);
  }
}

TEST_CASE( "it should measure multiple times" , "[measure]") {
  std::mt19937 mt(TEST_SEED);
  SECTION ( "when running once should be equal to one run measurement" ){
    auto stats = RandomWalkGenerator::measure(
        &mt, // twister reference
        10, // max order
        2, // steps
        3 // initial order
        );

    auto acc_stats = RandomWalkGenerator::accumulate_measure(
        &mt, // twister reference
        1,  // runs
        10, // max order
        2, // steps
        3 // initial order
        );

    REQUIRE( acc_stats.degree_distribution == stats.degree_distribution );
    REQUIRE( acc_stats.vertices_per_depth == stats.vertices_per_depth );
  }
}
