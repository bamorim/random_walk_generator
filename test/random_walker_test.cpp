#include<stdio.h>
#include<random_walker.hpp>
#include<graph.hpp>
#include<catch.hpp>
#define TEST_SEED 0

/*
 * This is testing a random behaviour
 * So we'll be using seed 0 always and
 * we'll check the results and see if they fit
 * so this is more like a regression test.
 */

TEST_CASE( " The random walker walks " ){
  // Lets make a cycle with 10 steps
  Graph g;
  g.add_vertex();
  for(int i = 0; i < 9; i++){
    g.add_vertex();
    g.add_edge(i, i+1);
  }
  g.add_edge(0,9);

  RandomWalker walker(TEST_SEED, &g);

  SECTION( "it should start on vertex 0" ){
    REQUIRE( walker.location() == 0 );
  }

  // From now on, this is a regression test
  int next_positions[] = {9, 0, 9, 0, 9, 0, 9, 0, 1, 2, 3, 2, 1, 0, 9, 8, 9, 8, 7, 6, 7, 8, 9, 8, 9, 8, 9, 0, 1, 0, 1, 2, 1, 0, 9, 0, 9, 8, 9, 0, 9, 8, 9, 0, 1, 2, 3, 4, 3, 4 };
  for(int i : next_positions){
    REQUIRE(walker.take_step() == i);
  }
}
