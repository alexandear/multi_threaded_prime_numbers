#include "Server.h"

#include <vector>
#include <iostream>
#include <algorithm>
#include <thread>

#include "Socket.h"
#include "PrimeNumberGenerator.h"

namespace server
{
using namespace red;

void Server::Run()
{
    try
    {
        TcpServerSocket socket(m_port);

        for (;;)
        {
            auto clientSocket = std::unique_ptr<TcpSocket>(socket.Accept());

            std::thread thread([&]() { HandleRequest(std::move(clientSocket)); });
            thread.join();
        }
    }
    catch (const SocketException& e)
    {
        std::cerr << "SocketException: " << e.what() << '\n';
    }
}

void Server::HandleRequest(std::unique_ptr<TcpSocket> socket) const
{
    try
    {
        constexpr int BufferSize = 1024;
        std::vector<char> buffer(BufferSize);
        socket->Recv(buffer.data(), std::size(buffer));

        Interval interval(std::string(std::begin(buffer), std::end(buffer)));
        std::cout << "Received interval: " << interval.ToString() << '\n';

        auto generator = PrimeNumberGenerator(interval);
        std::string sendData = generator.GetNumbers().ToString();
        socket->Send(sendData.c_str(), std::size(sendData));
        std::cout << "Sent numbers: " << sendData << '\n';
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
} // namespace server
