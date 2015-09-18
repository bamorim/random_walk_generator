#include<catch.hpp>
#include<graph.hpp>
#include<sstream>

TEST_CASE( "vertices can be checked and added to a graph", "[graph]" ){
  Graph g;
  
  REQUIRE( g.order() == 0 );
  REQUIRE( g.size() == 0 );

  SECTION( "adding vertices" ){
    g.addVertex();

    REQUIRE( g.order() == 1);
    REQUIRE( g.size() == 0);
  }
};

TEST_CASE( "edges can be added to a graph", "[graph]" ){
  Graph g;
  for(int i = 0; i < 5; i++) {
    g.addVertex();
  }

  REQUIRE( g.order() == 5 );

  SECTION( "add edge should increase the size" ){
    g.addEdge(0,1);
    REQUIRE( g.size() == 1);
    g.addEdge(1,2);
    REQUIRE( g.size() == 2);
  }
};
