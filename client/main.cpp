#include <iostream>

#include "Xml.h"
#include "Client.h"

int main()
{
    using namespace red;

    try
    {
        constexpr auto InputXml = "in.xml";
        constexpr auto OutputXml = "out.xml";
        constexpr auto ServerHost = "localhost";
        constexpr auto ServerPort = 3000;

        client::Client client;
        client.LoadIntervals(InputXml);
        std::cout << "Loaded intervals from '" << InputXml << "':\n";
        for (const auto& interval : client.GetIntervals())
            std::cout << interval.ToString() << '\n';

        client.ReceivePrimesFromServer({ServerHost, ServerPort});
        std::cout << "Received server-calculated prime numbers:\n";
        for (auto number : client.GetReceivedPrimeNumbers())
            std::cout << number << ' ';
        std::cout << '\n';

        client.SaveUniquePrimes(OutputXml);
        std::cout << "Saved prime numbers to '" << OutputXml << "':\n";
        for (auto number : client.GetUniquePrimeNumbers())
            std::cout << number << ' ';
        std::cout << '\n';
    }
    catch (const FstreamException& e)
    {
        std::cerr << "FstreamException: " << e.what() << '\n';
    }
    catch (const xml::Exception& e)
    {
        std::cerr << "xml::Exception: " << e.what() << '\n';
    }
    catch (const std::invalid_argument& e)
    {
        std::cerr << "std::invalid_argument: " << e.what() << '\n';
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
