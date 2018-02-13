#include "Utils.h"

#include <iostream>

namespace red
{
Ifstream::Ifstream(const std::string& path) : std::ifstream(path)
{
    if (!is_open())
        throw FstreamException("error while openning file");
}

Ifstream::~Ifstream()
{
    try
    {
        close();
    }
    catch (const failure& e)
    {
        std::cerr << "std::ios_base::failure: " << e.what() << "\n";
    }
}

Ofstream::Ofstream(const std::string& path) : std::ofstream(path)
{
    if (!is_open())
        throw FstreamException("error while openning file");
}

Ofstream::~Ofstream()
{
    try
    {
        close();
    }
    catch (const failure& e)
    {
        std::cerr << "std::ios_base::failure: " << e.what() << "\n";
    }
}

std::vector<std::string> Split(const std::string& str, char delimiter)
{
    std::vector<std::string> result;
    Split(str, delimiter, std::back_inserter(result));
    return result;
}
} // namespace red
