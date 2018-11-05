#include "Transact.hpp"

namespace comm {

Transact::Transact(const Socket& rSockP, EndPoint& rEndPointP)
  : rSockM(rSockP),
    rEndPointM(rEndPointP)
{
}

} /* namespace comm */



