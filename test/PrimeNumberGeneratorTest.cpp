#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "PrimeNumberGenerator.h"

using namespace red;
using namespace Catch::Matchers;

TEST_CASE("When passed correct parameters returns valid vector with prime numbers", "[Generate]")
{
    CHECK_THAT(PrimeNumberGenerator::Generate(2, 14),
               Equals(std::vector<std::size_t>({2, 3, 5, 7, 11, 13})));
    CHECK(PrimeNumberGenerator::Generate(2, 1031).back() == 1031);
    CHECK(PrimeNumberGenerator::Generate(2, 10000).back() == 9973);
}

TEST_CASE("When passed invalid parameters throws", "[Generate]")
{
    CHECK_THROWS(PrimeNumberGenerator::Generate(0, 0));
    CHECK_THROWS(PrimeNumberGenerator::Generate(200, 100));
    CHECK_THROWS(PrimeNumberGenerator::Generate(100, 1000000000));
}
