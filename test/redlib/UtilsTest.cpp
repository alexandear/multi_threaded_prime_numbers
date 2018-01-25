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

TEST_CASE("When passed different string returns vector", "[Split]")
{
    CHECK(Split("", ' ').empty());
    CHECK_THAT(Split(" ", ' '), Equals(std::vector<std::string>({""})));
    CHECK_THAT(Split("  ", ' '), Equals(std::vector<std::string>({"", ""})));
    CHECK_THAT(Split("1", ' '), Equals(std::vector<std::string>({"1"})));
    CHECK_THAT(Split("67565 ", ' '), Equals(std::vector<std::string>({"67565"})));
    CHECK_THAT(Split("12 34 56 78", ' '),
               Equals(std::vector<std::string>({"12", "34", "56", "78"})));
}
