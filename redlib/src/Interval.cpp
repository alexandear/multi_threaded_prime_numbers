#include "Interval.h"

#include <stdexcept>

#include "PrimeNumberGeneratorConstants.h"

namespace red
{
Interval::Interval(std::size_t low, std::size_t high) : m_low(low), m_high(high)
{
    Init(low, high);
}

Interval::Interval(const std::string& str) : Interval()
{
    auto numbers = Split(str, PrimeNumbersDelimiter);
    if (std::size(numbers) != 2)
        throw std::invalid_argument("must be two numbers");

    std::size_t low = std::stoul(numbers[0]);
    std::size_t high = std::stoul(numbers[1]);
    Init(low, high);
}

std::string Interval::ToString() const
{
    return std::to_string(m_low) + PrimeNumbersDelimiter + std::to_string(m_high);
}

void Interval::Init(std::size_t low, std::size_t high)
{
    if (low > high)
        throw std::invalid_argument("low > high");

    m_low = low;
    m_high = high;
}

bool operator==(const Interval& lhs, const Interval& rhs)
{
    return lhs.m_low == rhs.m_low && lhs.m_high == rhs.m_high;
}
} // namespace red
