#pragma once

#include <string>
#include <stdexcept>

namespace red
{
class SocketException : public std::runtime_error
{
public:
    explicit SocketException(const std::string& msg);
};

class Socket
{
public:
    virtual ~Socket();
    Socket(const Socket&) = delete;
    void operator=(const Socket&) = delete;
    Socket(Socket&&) noexcept = delete;
    Socket& operator=(Socket&&) noexcept = delete;

    std::string GetLocalAddress() const;
    uint16_t GetLocalPort() const;

    void SetLocalPort(uint16_t localPort);

protected:
    Socket(int type, int protocol);
    explicit Socket(int sockDesc) : m_sockDesc(sockDesc) {}

    int m_sockDesc;
};

class CommunicatingSocket : public Socket
{
public:
    std::string GetForeignAddress() const;
    uint16_t GetForeignPort() const;

    void Connect(const std::string& foreignAddress, uint16_t foreignPort);
    void Send(const void* buffer, int bufferLen);
    int Recv(void* buffer, int bufferLen);

protected:
    CommunicatingSocket(int type, int protocol);
    explicit CommunicatingSocket(int newConnSD);
};

class TcpSocket : public CommunicatingSocket
{
public:
    TcpSocket();
    TcpSocket(const std::string& foreignAddress, uint16_t foreignPort);

    static TcpSocket* Create(int newConnSd);

private:
    explicit TcpSocket(int newConnSd);
};

class TcpServerSocket : public Socket
{
public:
    explicit TcpServerSocket(uint16_t localPort, int queueLen = 5);

    TcpSocket* Accept();

private:
    void SetListen(int queueLen);
};
} // namespace red
