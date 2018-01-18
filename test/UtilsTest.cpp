#include "catch.hpp"

#include "Utils.h"

using namespace red;
using namespace Catch::Matchers;

TEST_CASE("When passed vector returns string", "[Join]")
{
    CHECK(Join(std::vector<int>(), ' ').empty());
    CHECK(Join(std::vector<int>({1, 2, 3, 4, 5}), ',') == "1,2,3,4,5");
    CHECK(Join(std::vector<std::string>({"12"}), ' ') == "12");
}
