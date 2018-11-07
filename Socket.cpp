#include "Socket.hpp"

#include "EndPoint.hpp"
#include "Helpers.hpp"

#include <unistd.h>

namespace comm {

Socket::Socket(const EndPoint& endPointP)
  : rEndPointM(endPointP)
{
    // Create socket
    sockFdM = ::socket(AF_INET, SOCK_DGRAM, 0);
    err::onSystemError(sockFdM < 0, "socket creation failed");

    // Bind socket to endpoint address
    auto addr = rEndPointM.addr();
    auto ret = ::bind(sockFdM, (struct sockaddr*) &addr, sizeof(addr));
    err::onSystemError(ret < 0, "bind failed");
}

Socket::~Socket()
{
    ::close(sockFdM);
}

Socket::operator int() const
{
    return sockFdM;
}

} /* namespace comm */
