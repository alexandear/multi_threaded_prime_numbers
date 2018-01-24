#include "Client.h"

#include <iostream>

#include "Xml.h"
#include "Socket.h"

namespace client
{
using namespace red;

Client::Client(const std::string& filePath, SocketAddress server) : m_server(std::move(server))
{
    xml::Document inDocument = xml::File::Read(filePath);
    auto xmlIntervals = inDocument.GetRoot()
                            .GetFirstChild("root")
                            ->GetFirstChild("intervals")
                            ->GetChildren("interval");

    for (const auto* xmlInterval : xmlIntervals)
    {
        int low = xmlInterval->GetFirstChild("low")->GetValue().ToInt();
        int high = xmlInterval->GetFirstChild("high")->GetValue().ToInt();
        m_intervals.emplace_back(low, high);
    }
}

void Client::Run()
{
    SendRecvPrimeNumbers(m_intervals.back());
    // std::vector<std::thread> threads;
    // for (auto interval : m_intervals)
    //    threads.emplace_back([=] { SendRecvPrimeNumbers(interval); });

    // for (auto& th : threads)
    //    th.join();
}

void Client::SendRecvPrimeNumbers(Interval interval)
{
    try
    {
        TCPSocket sock(m_server.GetHost().c_str(), m_server.GetPort());

        std::string info =
            "Interval: " + Join(std::vector<std::size_t>{interval.first, interval.second}, ' ');
        sock.send(info.c_str(), std::size(info));
    }
    catch (const SocketException& e)
    {
        std::cerr << "SocketException: " << e.what() << '\n';
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
}
