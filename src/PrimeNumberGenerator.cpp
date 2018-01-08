#include "PrimeNumberGenerator.h"

#include <cmath>
#include <stdexcept>

namespace red
{
// https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
std::vector<size_t> PrimeNumberGenerator::Generate(unsigned int n)
{
    if (n > MaxN)
    {
        throw std::invalid_argument("n > MaxN");
    }

    std::vector<bool> a(n + 1, true);
    for (size_t i = 2; i <= std::sqrt(n); i++)
    {
        if (a[i])
        {
            for (size_t j = i * i; j <= n; j += i)
            {
                a[j] = false;
            }
        }
    }

    std::vector<size_t> result;
    for (size_t i = 2; i < std::size(a); i++)
    {
        if (a[i])
        {
            result.push_back(i);
        }
    }

    return result;
}
}