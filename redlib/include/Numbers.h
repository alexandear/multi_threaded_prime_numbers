#pragma once

#include <string>
#include <vector>

namespace red
{
class Numbers
{
public:
    using DataType = std::vector<std::size_t>;

    Numbers() = default;
    explicit Numbers(DataType data) : m_data(std::move(data)) {}
    explicit Numbers(const std::string& str);

    std::string ToString() const;
    auto begin() const noexcept { return std::begin(m_data); }
    auto end() const noexcept { return std::end(m_data); }
    auto empty() const noexcept { return std::empty(m_data); }
    auto size() const noexcept { return std::size(m_data); }

    template <typename Iter>
    void Assign(Iter first, Iter last);

private:
    DataType m_data;
};

template <typename Iter>
void Numbers::Assign(Iter first, Iter last)
{
    m_data.assign(first, last);
}
}
