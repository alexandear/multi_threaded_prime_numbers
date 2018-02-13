#include "Client.h"

#include <iostream>
#include <algorithm>
#include <set>
#include <thread>

#include "Xml.h"
#include "Socket.h"

namespace client
{
using namespace red;

Client& Client::LoadIntervals(const std::string& filePath)
{
    InputXml xml(xml::File::Read(filePath));
    m_intervals = xml.GetIntervals();
    return *this;
}

Client& Client::ReceivePrimesFromServer(const SocketAddress& address)
{
    m_receivedPrimeNumbers.clear();
    std::vector<std::thread> threads;
    threads.reserve(std::size(m_intervals));
    for (auto interval : m_intervals)
        threads.emplace_back([=] { ReceivePrimesFromServerForInterval(address, interval); });

    for (auto& th : threads)
        th.join();

    return *this;
}

void Client::ReceivePrimesFromServerForInterval(const SocketAddress& address, Interval interval)
{
    try
    {
        TcpSocket sock(address.GetHost(), address.GetPort());

        std::string info = interval.ToString();
        sock.Send(info.c_str(), std::size(info));

        constexpr int BufferSize = 1024;
        std::vector<char> buffer(BufferSize);
        int bytesReceived;
        do
        {
            bytesReceived = sock.Recv(buffer.data(), std::size(buffer));
            if (bytesReceived == -1)
                throw SocketException("Unable to read");
        } while (bytesReceived != 0);
        Numbers numbers(std::string(std::cbegin(buffer), std::cend(buffer)));
        StorePrimesToSharedContainer(numbers);
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

void Client::StorePrimesToSharedContainer(const Numbers& receivedNumbers)
{
    std::copy(std::cbegin(receivedNumbers),
              std::cend(receivedNumbers),
              std::back_inserter(m_receivedPrimeNumbers));
}

Client& Client::SaveUniquePrimes(const std::string& filePath)
{
    std::set<size_t> unique(std::cbegin(m_receivedPrimeNumbers), std::cend(m_receivedPrimeNumbers));
    m_uniquePrimeNumbers.Assign(std::cbegin(unique), std::cend(unique));
    OutputXml xml(m_uniquePrimeNumbers);
    xml::File::Write(filePath, xml.GetDocument());

    return *this;
}

InputXml::InputXml(const xml::Document& document)
{
    auto intervalTags =
        document.GetRoot().GetFirstChild(Root)->GetFirstChild(Intervals)->GetChildren(Interval);

    for (const auto* tag : intervalTags)
    {
        std::size_t low = tag->GetFirstChild(Low)->GetValue().ToInt();
        std::size_t high = tag->GetFirstChild(High)->GetValue().ToInt();
        m_intervals.emplace_back(low, high);
    }
}

OutputXml::OutputXml(const Numbers& numbers)
{
    m_document.AddRoot(Root)->AddChild(Primes, xml::Value(numbers.ToString()));
}
} // namespace client
