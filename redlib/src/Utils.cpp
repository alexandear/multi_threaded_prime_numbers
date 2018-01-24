#include "Utils.h"

namespace red
{
Ifstream::Ifstream(const std::string& path) : std::ifstream(path)
{
    if (!is_open())
        throw IfstreamException("error while openning file");
}

Ifstream::~Ifstream()
{
    close();
}
} // namespace red
