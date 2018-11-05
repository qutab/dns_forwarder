#include "Send.hpp"

#include "Helpers.hpp"

namespace comm {

Send::Send(const Socket& rSockP, EndPoint& rDestP, std::vector<uint8_t>& rBufferP)
  : Transact(rSockP, rDestP, rBufferP)
{
}

int Send::operator ()()
{
    auto dstAddr = rEndPointM.addr();
    socklen_t dstAddrLen = sizeof(dstAddr);

    ssize_t count = sendto(rSockM,
        rBufferM.data(),
        rBufferM.size(),
        0,
        (struct sockaddr*)&dstAddr,
        dstAddrLen);

    helpers::exitIfError(count < 0, "send failed");

    return count;
}

} /* namespace comm */
