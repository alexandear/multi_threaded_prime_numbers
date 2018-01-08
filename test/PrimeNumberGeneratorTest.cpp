#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "PrimeNumberGenerator.h"

using namespace red;
using namespace Catch::Matchers;

TEST_CASE( "When passed correct parameter returns valid vector with prime numbers", "[Generate]" ) {
    CHECK_THAT( PrimeNumberGenerator::Generate(14), Equals(std::vector<std::size_t>({2, 3, 5, 7, 11, 13})) );
    CHECK( PrimeNumberGenerator::Generate(1031).back() == 1031 );
    CHECK( PrimeNumberGenerator::Generate(10000).back() == 9973 );
}

TEST_CASE( "When passed zero returns empty vector", "[Generate]" ) {
    CHECK( PrimeNumberGenerator::Generate(0).empty() );
}

TEST_CASE( "When passed very big n throws", "[Generate]" ) {
    CHECK_THROWS( PrimeNumberGenerator::Generate(10001) );
}
