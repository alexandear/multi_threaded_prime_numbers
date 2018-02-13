#pragma once

#include <memory>

namespace red
{
class TcpSocket;
} // namespace red

namespace server
{
class Server
{
public:
    explicit Server(int port) : m_port(static_cast<uint16_t>(port)) {}

    void Run();
    void HandleRequest(std::unique_ptr<red::TcpSocket> socket) const;

private:
    uint16_t m_port;
};
} // namespace server
