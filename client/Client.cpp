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
        TCPSocket sock(address.GetHost(), address.GetPort());

        std::string info = interval.ToString();
        sock.send(info.c_str(), std::size(info));

        constexpr int BufferSize = 1024;
        std::vector<char> buffer(BufferSize);
        int bytesReceived;
        do
        {
            bytesReceived = sock.recv(buffer.data(), std::size(buffer));
            if (bytesReceived == -1)
                throw SocketException("Unable to read");
        } while (bytesReceived != 0);
        auto numbers = ParseReceivedData(buffer);
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

std::vector<std::size_t> Client::ParseReceivedData(const std::vector<char>& data)
{
    auto primes = Split(std::string(std::begin(data), std::end(data)), PrimeNumbersDelimiter);
    std::vector<std::size_t> result;
    result.reserve(std::size(primes));
    std::transform(std::cbegin(primes),
                   std::cend(primes),
                   std::back_inserter(result),
                   [](const std::string& element) { return std::stoi(element); });
    return result;
}

void Client::StorePrimesToSharedContainer(const std::vector<std::size_t>& receivedNumbers)
{
    std::copy(std::cbegin(receivedNumbers),
              std::cend(receivedNumbers),
              std::back_inserter(m_receivedPrimeNumbers));
}

Client& Client::SaveUniquePrimes(const std::string& filePath)
{
    m_uniquePrimeNumbers = {std::cbegin(m_receivedPrimeNumbers), std::cend(m_receivedPrimeNumbers)};
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

OutputXml::OutputXml(const std::set<std::size_t>& numbers)
{
    std::string primes = Join(numbers, PrimeNumbersDelimiter);
    m_document.AddRoot(Root)->AddChild(Primes, xml::Value(primes));
}
} // namespace client
