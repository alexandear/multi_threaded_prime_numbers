#include "catch.hpp"

#include "Client.h"

using namespace red;
using namespace Catch::Matchers;

TEST_CASE("When passed valid document to InputXml returns intervals", "[GetIntervals]")
{
    xml::Document document(R"(
        <root>
          <intervals>
            <interval>
              <low>20</low>
              <high>400</high>
            </interval>
            <interval>
              <low>50</low>
              <high>150</high>
            </interval>
          </intervals>
        </root>
    )");

    auto result = client::InputXml(document).GetIntervals();

    CHECK(std::size(result) == 2);
    CHECK_THAT(result, Equals(std::vector<red::Interval>({{20, 400}, {50, 150}})));
}

TEST_CASE("When passed valid numbers to OutputXml returns document", "[GetDocument]")
{
    std::set<std::size_t> primes = {5, 7, 11, 13, 17, 19, 23, 29, 31};

    auto result = client::OutputXml(primes).GetDocument();

    auto rootTag = result.GetRoot().GetFirstChild();
    CHECK_THAT(rootTag->GetName(), Equals("root"));
    CHECK(std::size(rootTag->GetChildren()) == 1);
    auto primesTag = rootTag->GetFirstChild();
    CHECK_THAT(primesTag->GetName(), Equals("primes"));
    CHECK_THAT(primesTag->GetValue().ToString(), Equals("5 7 11 13 17 19 23 29 31"));
}
