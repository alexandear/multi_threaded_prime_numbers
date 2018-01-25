#pragma once

#include <string>

namespace red
{
class SocketAddress
{
public:
    SocketAddress(std::string host, int port);

    std::string GetHost() const { return m_host; }
    unsigned short GetPort() const { return m_port; }

private:
    std::string m_host;
    unsigned short m_port;
};

inline SocketAddress::SocketAddress(std::string host, int port)
    : m_host(std::move(host)), m_port(static_cast<unsigned short>(port))
{
}
}
