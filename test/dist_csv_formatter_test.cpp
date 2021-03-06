#include<dist_csv_formatter.hpp>
#include<catch.hpp>

TEST_CASE( "It should output correct csv" ){
  std::vector<uint_fast32_t> values = {10,20,0,30};
  std::stringstream output;

  SECTION( "When we say to not include headers" ) {
    DistCsvFormatter::format(values, output, false);
    REQUIRE( output.str() == "0,10\n1,20\n3,30\n" );
  }

  SECTION( "When we don't say anything" ){
    DistCsvFormatter::format(values, output);
    REQUIRE( output.str() == "0,10\n1,20\n3,30\n" );
  }

  SECTION( "When we say to include headers" ) {
    DistCsvFormatter::format(values, output, true);
    REQUIRE( output.str() == "value,count\n0,10\n1,20\n3,30\n" );
  }

  SECTION( "When the first one is 0" ) {
    DistCsvFormatter::format({0,10}, output, true);
    REQUIRE( output.str() == "value,count\n1,10\n" );
  }
}
