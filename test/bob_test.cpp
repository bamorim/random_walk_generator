#include "catch.hpp"
#include<bob.hpp>
#include<sstream>

TEST_CASE( "Bob says hello", "[bob]" ) {
  Bob b;
  std::stringstream ss;

  b.SayHello(ss);

  REQUIRE( "Hello World!\n" == ss.str() );
}
