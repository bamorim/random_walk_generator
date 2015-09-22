#include<catch.hpp>
#define private public
#include<graph.hpp>

TEST_CASE( "vertices can be checked and added to a graph", "[graph]" ){
  Graph g;
  
  REQUIRE( g.order() == 0 );
  REQUIRE( g.size() == 0 );

  SECTION( "adding vertices" ){
    g.add_vertex();

    REQUIRE( g.order() == 1);
    REQUIRE( g.size() == 0);
  }
};

TEST_CASE( "we can preallocate space on the adjacency vector", "[graph]" ){
  Graph g(1000);
  REQUIRE( g.order() == 0);
  REQUIRE( g.size() == 0);
  REQUIRE( g.adjacency_vector.size() == 0 );
  REQUIRE( g.adjacency_vector.capacity() == 1000 );
}

TEST_CASE( "adding edges to a graph", "[graph]" ){
  Graph g;
  g.add_vertex();
  for(int i = 0; i < 3; i++) {
    g.add_vertex();
    g.add_edge(0,i+1);
  }

  REQUIRE( g.order() == 4 );

  SECTION( "add edge should increase the size" ){
    REQUIRE( g.size() == 3 );
  }

  SECTION( "Should get a vector of neighbors" ){
    REQUIRE( g.neighbors_of(0)->at(0) == 1 );
    REQUIRE( g.neighbors_of(0)->at(1) == 2 );
    REQUIRE( g.neighbors_of(0)->at(2) == 3 );
  }

  SECTION( "Edges should be undirected" ){
    REQUIRE( g.neighbors_of(1)->size() == 1 );
  }
}
