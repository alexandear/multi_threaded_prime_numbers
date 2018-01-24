#include <iostream>

#include "Xml.h"
#include "Utils.h"
#include "Client.h"

int main()
{
    using namespace red;

    try
    {
        client::Client client("in.xml", std::make_pair("localhost", unsigned short{3000}));
        client.Run();
    }
    catch (const FstreamException& e)
    {
        std::cerr << "FstreamException: " << e.what() << '\n';
    }
    catch (const xml::Exception& e)
    {
        std::cerr << "xml::Exception: " << e.what() << '\n';
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
