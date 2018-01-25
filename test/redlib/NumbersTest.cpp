#include "catch.hpp"

#include "Numbers.h"

using namespace red;
using namespace Catch::Matchers;

TEST_CASE("When passed vector returns valid string", "[ToString]")
{
    CHECK_THAT(Numbers(std::vector<std::size_t>{1, 2, 3}).ToString(), Equals("1 2 3"));
}
