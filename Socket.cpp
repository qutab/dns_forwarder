#include "Socket.hpp"

#include "Helpers.hpp"

#include <arpa/inet.h>

namespace comm {

Socket::Socket(const EndPoint& endPointP)
  : rEndPointM(endPointP)
{
    // Create socket
    sockFdM = socket(AF_INET, SOCK_DGRAM, 0);
    helpers::exitIfError(sockFdM < 0, "socket creation failed");

    // Bind socket to endpoint address
    auto addr = rEndPointM.addr();
    auto ret = bind(sockFdM, (struct sockaddr*) &addr, sizeof(addr));
    helpers::exitIfError(ret < 0, "bind failed");
}

Socket::operator int() const
{
    return sockFdM;
}

} /* namespace comm */
