#pragma once

#include <vector>
#include <set>
#include <thread>

#include "Utils.h"

namespace red
{
class PrimeNumberGenerator
{
public:
    using Interval = std::pair<std::size_t, std::size_t>;
    static constexpr unsigned int MaxN = 10000000;

    explicit PrimeNumberGenerator(std::vector<Interval> intervals);

    std::set<std::size_t> Calculate();

    static std::vector<std::size_t> Generate(std::size_t low, std::size_t high);

private:
    void GenerateIntoSharedContainer(Interval interval);

    std::vector<Interval> m_intervals;
    SharedVector<std::size_t> m_generatedNumbers;
};
} // namespace red
