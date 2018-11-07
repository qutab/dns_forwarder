#include "Receive.hpp"

#include "EndPoint.hpp"
#include "Helpers.hpp"

#include <arpa/inet.h>
#include <netinet/in.h>

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

    err::onSystemError(count < 0, "recvfrom failed");

    // check truncated
    if (count == static_cast<ssize_t>(bufferSize))
    {
        log::logWarn("Datagram too large. Truncated");
    }

    char ipStr[INET_ADDRSTRLEN];
    auto ret = inet_ntop(srcAddr.sin_family, &(srcAddr.sin_addr), ipStr, INET_ADDRSTRLEN);
    err::onSystemError(ret == NULL, "invalid ip");

    rEndPointM = EndPoint(ipStr, ntohs(srcAddr.sin_port));

    return count;
}

} /* namespace comm */
