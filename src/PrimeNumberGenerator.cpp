#include "PrimeNumberGenerator.h"

#include <cmath>
#include <stdexcept>

namespace red
{
// https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
std::vector<std::size_t> PrimeNumberGenerator::Generate(std::size_t low, std::size_t high)
{
    if (high > MaxN || low > high || low < 2)
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

    std::vector<size_t> result;
    for (std::size_t i = low; i < std::size(a); i++)
    {
        if (a[i])
            result.push_back(i);
    }

    return result;
}
} // namespace red
