#include "Receive.hpp"

#include "Helpers.hpp"

#include <arpa/inet.h>
#include <sys/types.h>
#include <iostream>
#include <cassert>
#include <unistd.h>
#include <cstring>
#include <sstream>
#include <vector>

namespace comm {

namespace {

void checkTruncated(bool truncCondP)
{
    if (truncCondP)
    {
        std::cout << "[WARN] Datagram too large for buffer. Truncated." << std::endl;
    }
} // anonymous namespace

}


Receive::Receive(const Socket& rSockP, EndPoint& rSrcP, std::vector<uint8_t>& rBufferP)
  : Transact(rSockP, rSrcP, rBufferP)
{
}

int Receive::operator ()()
{
    auto srcAddr = rEndPointM.addr();
    socklen_t srcAddrLen = sizeof(srcAddr);
    auto bufferSize = rBufferM.size();

    ssize_t count = recvfrom(rSockM,
        rBufferM.data(),
        bufferSize,
        0,
        (struct sockaddr*)&srcAddr,
        &srcAddrLen);

    helpers::exitIfError(count < 0, "recvfrom failed");
    checkTruncated(count == static_cast<ssize_t>(bufferSize));

    rBufferM.resize(count);

    rEndPointM = EndPoint(inet_ntoa(srcAddr.sin_addr), ntohs(srcAddr.sin_port));

    return count;
}

} /* namespace comm */
