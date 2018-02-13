#include "catch.hpp"

#include "Numbers.h"

#include <list>

using namespace red;
using namespace Catch::Matchers;

TEST_CASE("When passed vector returns valid string", "[ToString]")
{
    CHECK_THAT(Numbers(std::vector<std::size_t>{1, 2, 3}).ToString(), Equals("1 2 3"));
}

TEST_CASE("When empty and non-empty container returns valid value", "[empty]")
{
    CHECK_FALSE(Numbers(std::vector<std::size_t>{1, 2, 3}).empty());
    CHECK(Numbers(std::vector<std::size_t>{}).empty());
}

TEST_CASE("When passed list iterators should create from it", "[Assign]")
{
    std::list<std::size_t> source{1, 2, 3};
    Numbers numbers; 

    numbers.Assign(std::begin(source), std::end(source));

    CHECK(3 == std::size(numbers));
}
