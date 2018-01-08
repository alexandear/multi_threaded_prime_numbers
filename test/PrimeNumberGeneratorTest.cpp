#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "PrimeNumberGenerator.h"

using namespace red;
using namespace Catch::Matchers;

TEST_CASE( "When passed correct value returns valid prime numbers", "[Generate]" ) {
    CHECK_THAT( PrimeNumberGenerator::Generate(14), Equals(std::vector<size_t>({2, 3, 5, 7, 11, 13})) );
}
