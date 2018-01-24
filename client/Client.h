#pragma once

#include <utility>
#include <string>
#include <vector>

#include "Utils.h"
#include "Types.h"
#include "SocketTypes.h"

namespace client
{
class Client
{
public:
    explicit Client(const std::string& filePath, red::SocketAddress server);

    void Run();
    void SendRecvPrimeNumbers(red::Interval interval);

private:
    const red::SocketAddress m_server;
    std::vector<std::pair<std::size_t, std::size_t>> m_intervals;
    red::SharedVector<std::size_t> m_primeNumbers;
};
}
