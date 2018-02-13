#pragma once

#include <string>
#include <vector>

#include "Utils.h"
#include "Interval.h"
#include "SocketTypes.h"
#include "Xml.h"
#include "Numbers.h"

namespace client
{
class Client
{
public:
    Client() = default;

    const red::SharedVector<std::size_t>& GetReceivedPrimeNumbers() const;
    const std::vector<red::Interval>& GetIntervals() const { return m_intervals; }
    const red::Numbers& GetUniquePrimeNumbers() const { return m_uniquePrimeNumbers; }

    Client& LoadIntervals(const std::string& filePath);
    Client& ReceivePrimesFromServer(const red::SocketAddress& address);
    void ReceivePrimesFromServerForInterval(const red::SocketAddress& address,
                                            red::Interval interval);
    Client& SaveUniquePrimes(const std::string& filePath);

private:
    void StorePrimesToSharedContainer(const red::Numbers& receivedNumbers);

    std::vector<red::Interval> m_intervals;
    red::SharedVector<std::size_t> m_receivedPrimeNumbers;
    red::Numbers m_uniquePrimeNumbers;
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
    explicit OutputXml(const red::Numbers& numbers);

    const red::xml::Document& GetDocument() const { return m_document; }

private:
    static constexpr auto Root = "root";
    static constexpr auto Primes = "primes";

    red::xml::Document m_document;
};
} // namespace client
