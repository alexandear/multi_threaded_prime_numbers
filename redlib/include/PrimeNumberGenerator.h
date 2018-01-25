#pragma once

#include <vector>

#include "Interval.h"

namespace red
{
class PrimeNumberGenerator
{
public:
    static constexpr unsigned int MaxN = 10000000;

    explicit PrimeNumberGenerator(Interval interval);

    const std::vector<std::size_t>& GetNumbers() const { return m_primes; }
    std::string ToString() const;

    // https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
    static std::vector<std::size_t> Generate(Interval interval);

private:
    std::vector<std::size_t> m_primes;
};
} // namespace red
