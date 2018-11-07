#include "Receive.hpp"

#include "EndPoint.hpp"
#include "Helpers.hpp"

#include <arpa/inet.h>

namespace comm {

Receive::Receive(const Socket& rSockP, EndPoint& rSrcP)
  : Transact(rSockP, rSrcP)
{
}

int Receive::operator ()(std::vector<uint8_t>& rBufferP)
{
    auto srcAddr = rEndPointM.addr();
    socklen_t srcAddrLen = sizeof(srcAddr);
    auto bufferSize = rBufferP.size();

    const ssize_t count = recvfrom(rSockM,
        rBufferP.data(),
        bufferSize,
        0,
        (struct sockaddr*)&srcAddr,
        &srcAddrLen);

    log::logSystemError(count < 0, "recvfrom failed");

    // check truncated
    if (count == static_cast<ssize_t>(bufferSize))
    {
        log::logWarn("Datagram too large. Truncated");
    }

    rEndPointM = EndPoint(inet_ntoa(srcAddr.sin_addr), ntohs(srcAddr.sin_port));

    return count;
}

} /* namespace comm */
