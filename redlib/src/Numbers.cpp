#include "Numbers.h"

#include <algorithm>

#include "Utils.h"

namespace red
{
Numbers::Numbers(const std::string& str)
{
    auto numbersStr = Split(str, ' ');
    m_data.reserve(std::size(numbersStr));
    std::transform(std::cbegin(numbersStr),
                   std::cend(numbersStr),
                   std::back_inserter(m_data),
                   [](const std::string& elem) { return std::stoul(elem); });
}

std::string Numbers::ToString() const
{
    return Join(*this, ' ');
}
} // namespace red
