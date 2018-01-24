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
} // namespace red
