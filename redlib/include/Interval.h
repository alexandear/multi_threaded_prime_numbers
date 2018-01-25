#pragma once

#include <cstddef>

#include "Utils.h"

namespace red
{
class Interval
{
public:
    Interval() : Interval(0, 0) {}
    Interval(std::size_t low, std::size_t high);
    explicit Interval(const std::string& str);

    std::size_t GetLow() const { return m_low; }
    std::size_t GetHigh() const { return m_high; }
    std::string ToString() const;

    friend bool operator==(const Interval& lhs, const Interval& rhs);
    friend bool operator!=(const Interval& lhs, const Interval& rhs) { return !(lhs == rhs); }

private:
    void Init(std::size_t low, std::size_t high);

    std::size_t m_low;
    std::size_t m_high;
};
} // namespace red
