#include "PrimeNumberGenerator.h"

#include <cmath>
#include <stdexcept>

namespace red
{
PrimeNumberGenerator::PrimeNumberGenerator(Interval interval) : m_primes(Generate(interval)) {}

std::vector<std::size_t> PrimeNumberGenerator::Generate(Interval interval)
{
    std::size_t low = interval.GetLow();
    std::size_t high = interval.GetHigh();
    if (high > MaxN || low < 2)
        throw std::invalid_argument("high > MaxN or low > high or low < 2");

    std::vector<bool> a(high + 1, true);
    for (std::size_t i = 2; i <= std::sqrt(high); i++)
    {
        if (a[i])
        {
            for (std::size_t j = i * i; j <= high; j += i)
                a[j] = false;
        }
    }

    std::vector<std::size_t> result;
    result.reserve(std::size(a));
    for (std::size_t i = low; i < std::size(a); i++)
    {
        if (a[i])
            result.emplace_back(i);
    }

    return result;
}
} // namespace red
