#pragma once

#include <fstream>
#include <stdexcept>
#include <string>

namespace red
{
struct IfstreamException : std::runtime_error
{
    explicit IfstreamException(const char* msg) : std::runtime_error(msg) {}
};

class Ifstream : public std::ifstream
{
public:
    explicit Ifstream(const std::string& path);
    ~Ifstream();
    Ifstream(const Ifstream&) = delete;
    Ifstream& operator=(const Ifstream&) = delete;
    Ifstream(Ifstream&&) noexcept = default;
    Ifstream& operator=(Ifstream&&) noexcept = default;
};
} // namespace red
