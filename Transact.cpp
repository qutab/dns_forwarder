#include "Transact.hpp"

namespace comm {

Transact::Transact(const Socket& rSockP, EndPoint& rEndPointP, std::vector<uint8_t>& rBufferP)
  : rSockM(rSockP),
    rEndPointM(rEndPointP),
    rBufferM(rBufferP)
{
}

} /* namespace comm */



