#pragma once

#include "Socket.hpp"

#include <cstdint>
#include <vector>

namespace comm {

/** Abstract class representing a transaction over a socket to/from an EndPoint */
class Transact
{
public:
    /**
     * @param rSockP Socket over which the transaction takes place
     * @param rEndPointP Src or Dst endpoint
     */
    Transact(const Socket& rSockP, EndPoint& rEndPointP);

    virtual ~Transact() = default;

    /**
     * @return count of bytes in transaction
     * Precondition: Socket is bound to an interface
     * Postcondition: Transacted bytes are stored in buffer @rBufferP
     */
    virtual int operator()(std::vector<uint8_t>& rBufferP) = 0;

protected:
    const Socket& rSockM;
    EndPoint& rEndPointM;
};

} /* namespace comm */
