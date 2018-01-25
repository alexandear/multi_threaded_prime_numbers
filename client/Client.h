#pragma once

#include <set>
#include <string>
#include <vector>

#include "Utils.h"
#include "Interval.h"
#include "SocketTypes.h"
#include "Xml.h"

namespace client
{
class Client
{
public:
    Client() = default;

    const red::SharedVector<std::size_t>& GetReceivedPrimeNumbers() const;
    const std::vector<red::Interval>& GetIntervals() const { return m_intervals; }
    const std::set<std::size_t>& GetUniquePrimeNumbers() const { return m_uniquePrimeNumbers; }

    Client& LoadIntervals(const std::string& filePath);
    Client& ReceivePrimesFromServer(const red::SocketAddress& address);
    void ReceivePrimesFromServerForInterval(const red::SocketAddress& address,
                                            red::Interval interval);
    Client& SaveUniquePrimes(const std::string& filePath);

private:
    void StorePrimesToSharedContainer(const std::vector<std::size_t>& receivedNumbers);

    static std::vector<std::size_t> ParseReceivedData(const std::vector<char>& data);

    std::vector<red::Interval> m_intervals;
    red::SharedVector<std::size_t> m_receivedPrimeNumbers;
    std::set<std::size_t> m_uniquePrimeNumbers;
};

inline const red::SharedVector<std::size_t>& Client::GetReceivedPrimeNumbers() const
{
    return m_receivedPrimeNumbers;
}

class InputXml
{
public:
    explicit InputXml(const red::xml::Document& document);

    const std::vector<red::Interval>& GetIntervals() const { return m_intervals; }

private:
    static constexpr auto Root = "root";
    static constexpr auto Intervals = "intervals";
    static constexpr auto Interval = "interval";
    static constexpr auto Low = "low";
    static constexpr auto High = "high";

    std::vector<red::Interval> m_intervals;
};

class OutputXml
{
public:
    explicit OutputXml(const std::set<std::size_t>& numbers);

    const red::xml::Document& GetDocument() const { return m_document; }

private:
    static constexpr auto Root = "root";
    static constexpr auto Primes = "primes";

    red::xml::Document m_document;
};
}
