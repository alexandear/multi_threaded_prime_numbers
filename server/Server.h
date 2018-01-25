#pragma once

#include <memory>

namespace red
{
class TcpSocket;
}

namespace server
{
class Server
{
public:
    explicit Server(int port) : m_port(static_cast<unsigned short>(port)) {}

    void Run();
    void HandleRequest(std::unique_ptr<red::TcpSocket> socket) const;

private:
    unsigned short m_port;
};
} // namespace server
