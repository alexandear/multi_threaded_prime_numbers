#ifdef WIN32
#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#endif

#include "Socket.h"

#ifdef WIN32
#include <WinSock2.h>
#include <WS2tcpip.h>
using socklen_t = int;
using raw_type = char;
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
using raw_type = void;
#endif

#include <cstring>

namespace red
{
SocketException::SocketException(const std::string& msg) : runtime_error(msg.c_str()) {}

Socket::Socket(int type, int protocol)
{
#ifdef WIN32
    static bool initialized = false;
    if (!initialized)
    {
        WSADATA wsaData{};

        WORD wVersionRequested = MAKEWORD(2, 0);
        if (WSAStartup(wVersionRequested, &wsaData) != 0)
            throw SocketException("Unable to load WinSock DLL");
        initialized = true;
    }
#endif

    if ((m_sockDesc = socket(PF_INET, type, protocol)) < 0)
        throw SocketException("Socket creation failed (socket())");
}

Socket::~Socket()
{
#ifdef WIN32
    ::closesocket(m_sockDesc);
#else
    ::close(m_sockDesc);
#endif
    m_sockDesc = -1;
}

std::string Socket::GetLocalAddress() const
{
    sockaddr_in addr{};
    unsigned int addrLen = sizeof(addr);

    if (getsockname(m_sockDesc,
                    reinterpret_cast<sockaddr*>(&addr),
                    reinterpret_cast<socklen_t*>(&addrLen)) < 0)
        throw SocketException("Fetch of local address failed (getsockname())");

    return inet_ntoa(addr.sin_addr);
}

uint16_t Socket::GetLocalPort() const
{
    sockaddr_in addr{};
    unsigned int addrLen = sizeof(addr);

    if (getsockname(m_sockDesc,
                    reinterpret_cast<sockaddr*>(&addr),
                    reinterpret_cast<socklen_t*>(&addrLen)) < 0)
        throw SocketException("Fetch of local port failed (getsockname())");

    return ntohs(addr.sin_port);
}

void Socket::SetLocalPort(uint16_t localPort)
{
    sockaddr_in localAddr{};
    memset(&localAddr, 0, sizeof(localAddr));
    localAddr.sin_family = AF_INET;
    localAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    localAddr.sin_port = htons(localPort);

    if (bind(m_sockDesc, reinterpret_cast<sockaddr*>(&localAddr), sizeof(sockaddr_in)) < 0)
        throw SocketException("Set of local port failed (bind())");
}

CommunicatingSocket::CommunicatingSocket(int type, int protocol) : Socket(type, protocol) {}

CommunicatingSocket::CommunicatingSocket(int newConnSD) : Socket(newConnSD) {}

void CommunicatingSocket::Connect(const std::string& foreignAddress, uint16_t foreignPort)
{
    sockaddr_in destAddr{};
    destAddr.sin_family = AF_INET;

    hostent* host;
    if ((host = gethostbyname(foreignAddress.c_str())) == nullptr)
        throw SocketException("Failed to resolve name (gethostbyname())");
    destAddr.sin_addr.s_addr = *reinterpret_cast<unsigned long*>(host->h_addr_list[0]);

    destAddr.sin_port = htons(foreignPort);

    // Try to Connect to the given port
    if (::connect(m_sockDesc, reinterpret_cast<sockaddr*>(&destAddr), sizeof(destAddr)) < 0)
        throw SocketException("Connect failed (Connect())");
}

void CommunicatingSocket::Send(const void* buffer, int bufferLen)
{
    if (::send(m_sockDesc, static_cast<raw_type*>(const_cast<void*>(buffer)), bufferLen, 0) < 0)
        throw SocketException("Send failed (Send())");
}

int CommunicatingSocket::Recv(void* buffer, int bufferLen)
{
    int rtn;
    if ((rtn = ::recv(m_sockDesc, static_cast<raw_type*>(buffer), bufferLen, 0)) < 0)
        throw SocketException("Received failed (Recv())");

    return rtn;
}

std::string CommunicatingSocket::GetForeignAddress() const
{
    sockaddr_in addr{};
    unsigned int addr_len = sizeof(addr);

    if (getpeername(m_sockDesc,
                    reinterpret_cast<sockaddr*>(&addr),
                    reinterpret_cast<socklen_t*>(&addr_len)) < 0)
        throw SocketException("Fetch of foreign address failed (getpeername())");

    return inet_ntoa(addr.sin_addr);
}

uint16_t CommunicatingSocket::GetForeignPort() const
{
    sockaddr_in addr{};
    unsigned int addrLen = sizeof(addr);

    if (getpeername(m_sockDesc,
                    reinterpret_cast<sockaddr*>(&addr),
                    reinterpret_cast<socklen_t*>(&addrLen)) < 0)
        throw SocketException("Fetch of foreign port failed (getpeername())");

    return ntohs(addr.sin_port);
}

TcpSocket::TcpSocket() : CommunicatingSocket(SOCK_STREAM, IPPROTO_TCP) {}

TcpSocket::TcpSocket(const std::string& foreignAddress, uint16_t foreignPort)
    : CommunicatingSocket(SOCK_STREAM, IPPROTO_TCP)
{
    Connect(foreignAddress, foreignPort);
}

TcpSocket* TcpSocket::Create(int newConnSd)
{
    return new TcpSocket(newConnSd);
}

TcpSocket::TcpSocket(int newConnSd) : CommunicatingSocket(newConnSd) {}

TcpServerSocket::TcpServerSocket(uint16_t localPort, int queueLen)
    : Socket(SOCK_STREAM, IPPROTO_TCP)
{
    SetLocalPort(localPort);
    SetListen(queueLen);
}

TcpSocket* TcpServerSocket::Accept()
{
    int newConnSd;
    if ((newConnSd = ::accept(m_sockDesc, nullptr, nullptr)) < 0)
        throw SocketException("Accept failed (Accept())");

    return TcpSocket::Create(newConnSd);
}

void TcpServerSocket::SetListen(int queueLen)
{
    if (listen(m_sockDesc, queueLen) < 0)
        throw SocketException("Set listening socket failed (listen())");
}
} // namespace red
