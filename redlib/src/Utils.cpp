#include "Utils.h"

namespace red
{
Ifstream::Ifstream(const std::string& path) : std::ifstream(path)
{
    if (!is_open())
        throw FstreamException("error while openning file");
}

Ifstream::~Ifstream()
{
    close();
}

Ofstream::Ofstream(const std::string& path) : std::ofstream(path)
{
    if (!is_open())
        throw FstreamException("error while openning file");
}

Ofstream::~Ofstream()
{
    close();
}

std::vector<std::string> Split(const std::string& str, char delimiter)
{
    std::vector<std::string> result;
    Split(str, delimiter, std::back_inserter(result));
    return result;
}
} // namespace red
