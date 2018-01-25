#pragma once

#include <vector>
#include <set>

#include "Utils.h"
#include "PrimeNumberGeneratorTypes.h"

namespace red
{
class PrimeNumberGenerator
{
public:
    static constexpr unsigned int MaxN = 10000000;

    explicit PrimeNumberGenerator(std::vector<Interval> intervals);

    std::set<std::size_t> Calculate();

    // https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
    static std::vector<std::size_t> Generate(Interval interval);

private:
    void GenerateIntoSharedContainer(Interval interval);

    std::vector<Interval> m_intervals;
    SharedVector<std::size_t> m_generatedNumbers;
};
} // namespace red
