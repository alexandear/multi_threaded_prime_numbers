#pragma once

#include <string>
#include <vector>

namespace red
{
class Numbers : public std::vector<std::size_t>
{
public:
    Numbers() = default;
    explicit Numbers(std::vector<std::size_t> data) : std::vector<std::size_t>(std::move(data)) {}
    explicit Numbers(const std::string& str);

    std::string ToString() const;
};
}
