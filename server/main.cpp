#include <iostream>

#include "Server.h"

int main()
{
    try
    {
        constexpr auto Port = 3000;

        server::Server server(Port);
        server.Run();
    }
    catch (const std::exception& e)
    {
        std::cerr << "std::exception: " << e.what() << '\n';
    }
    catch (...)
    {
        std::cerr << "unknown exception\n";
    }
}
