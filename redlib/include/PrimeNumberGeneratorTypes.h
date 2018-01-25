#pragma once

#include <cstddef>
#include <stdexcept>

namespace red
{
constexpr char PrimeNumbersDelimiter = ' ';

class Interval
{
public:
    Interval() : Interval(0, 0) {}
    Interval(std::size_t low, std::size_t high);

    std::size_t GetLow() const { return m_low; }
    std::size_t GetHigh() const { return m_high; }
    std::string ToString() const;

    friend bool operator==(const Interval& lhs, const Interval& rhs);
    friend bool operator!=(const Interval& lhs, const Interval& rhs) { return !(lhs == rhs); }

private:
    std::size_t m_low;
    std::size_t m_high;
};

inline Interval::Interval(std::size_t low, std::size_t high) : m_low(low), m_high(high)
{
    if (low > high)
        throw std::invalid_argument("low > high");
}

inline std::string Interval::ToString() const
{
    return std::to_string(m_low) + PrimeNumbersDelimiter + std::to_string(m_high);
}

inline bool operator==(const Interval& lhs, const Interval& rhs)
{
    return lhs.m_low == rhs.m_low && lhs.m_high == rhs.m_high;
}
} // namespace red
