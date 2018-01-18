#pragma once

#include <vector>

namespace red
{
class PrimeNumberGenerator
{
public:
    static constexpr unsigned int MaxN = 10000000;

    static std::vector<std::size_t> Generate(std::size_t low, std::size_t high);
};
} // namespace red
