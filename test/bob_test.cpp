#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include<bob.hpp>
#include<sstream>

TEST_CASE( "Bob says hello" ) {
  Bob b;
  std::stringstream ss;

  b.SayHello(ss);

  REQUIRE( "Hello World!\n" == ss.str() );
}
