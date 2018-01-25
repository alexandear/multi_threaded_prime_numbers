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
    ~Socket();
    Socket(const Socket&) = delete;
    void operator=(const Socket&) = delete;
    Socket(Socket&&) noexcept = delete;
    Socket& operator=(Socket&&) noexcept = delete;

    std::string GetLocalAddress() const;
    unsigned short GetLocalPort() const;

    void SetLocalPort(unsigned short localPort);

protected:
    Socket(int type, int protocol);
    explicit Socket(int sockDesc) : m_sockDesc(sockDesc) {}

    int m_sockDesc;
};

class CommunicatingSocket : public Socket
{
public:
    std::string GetForeignAddress() const;
    unsigned short GetForeignPort() const;

    void Connect(const std::string& foreignAddress, unsigned short foreignPort);
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
    TcpSocket(const std::string& foreignAddress, unsigned short foreignPort);

private:
    explicit TcpSocket(int newConnSd);

    friend class TcpServerSocket;
};

class TcpServerSocket : public Socket
{
public:
    explicit TcpServerSocket(unsigned short localPort, int queueLen = 5);

    TcpSocket* Accept();

private:
    void SetListen(int queueLen);
};
} // namespace red
