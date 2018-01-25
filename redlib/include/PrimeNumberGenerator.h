#pragma once

#include <vector>

#include "Interval.h"
#include "Numbers.h"

namespace red
{
class PrimeNumberGenerator
{
public:
    static constexpr unsigned int MaxN = 10000000;

    explicit PrimeNumberGenerator(Interval interval);

    const Numbers& GetNumbers() const { return m_primes; }

    // https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
    static std::vector<std::size_t> Generate(Interval interval);

private:
    Numbers m_primes;
};
} // namespace red
