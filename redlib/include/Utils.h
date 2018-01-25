#pragma once

#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <mutex>
#include <sstream>

namespace red
{
struct FstreamException : std::runtime_error
{
    explicit FstreamException(const char* msg) : std::runtime_error(msg) {}
};

class Ifstream : public std::ifstream
{
public:
    explicit Ifstream(const std::string& path);
    ~Ifstream();
    Ifstream(const Ifstream&) = delete;
    Ifstream& operator=(const Ifstream&) = delete;
    Ifstream(Ifstream&&) noexcept = delete;
    Ifstream& operator=(Ifstream&&) noexcept = delete;
};

class Ofstream : public std::ofstream
{
public:
    explicit Ofstream(const std::string& path);
    ~Ofstream();
    Ofstream(const Ofstream&) = delete;
    Ofstream& operator=(const Ofstream&) = delete;
    Ofstream(Ofstream&&) noexcept = delete;
    Ofstream& operator=(Ofstream&&) noexcept = delete;
};

template <typename Element>
class SharedVector
{
public:
    const std::vector<Element>& GetData() const { return m_data; }
    void PushBack(Element element);
    void Clear() { m_data.clear(); }

private:
    std::recursive_mutex m_mutex;
    std::vector<Element> m_data;
};

template <typename Element>
void SharedVector<Element>::PushBack(Element element)
{
    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    m_data.push_back(element);
}

template <typename Container>
std::string Join(const Container& container, char delimiter)
{
    if (std::empty(container))
        return "";

    std::stringstream ss;
    auto it = std::cbegin(container);
    ss << *it++;
    for (; it != std::cend(container); ++it)
        ss << delimiter << *it;
    return ss.str();
}

template <typename Iterator>
void Split(const std::string& str, char delimiter, Iterator result)
{
    std::stringstream ss(str);
    std::string item;
    while (std::getline(ss, item, delimiter))
        *(result++) = item;
}

std::vector<std::string> Split(const std::string& str, char delimiter);
} // namespace red
