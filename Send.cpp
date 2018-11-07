#include "Send.hpp"

#include "EndPoint.hpp"
#include "Helpers.hpp"

#include <arpa/inet.h>

namespace comm {

Send::Send(const Socket& rSockP, EndPoint& rDestP)
  : Transact(rSockP, rDestP)
{
}

int Send::operator ()(std::vector<uint8_t>& rBufferP)
{
    auto dstAddr = rEndPointM.addr();
    socklen_t dstAddrLen = sizeof(dstAddr);

    const ssize_t count = sendto(rSockM,
        rBufferP.data(),
        rBufferP.size(),
        0,
        (struct sockaddr*)&dstAddr,
        dstAddrLen);

    err::onSystemError(count < 0, "send failed");

    return count;
}

} /* namespace comm */
