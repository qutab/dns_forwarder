#pragma once

#include "Socket.hpp"

#include <cstdint>
#include <vector>

namespace comm {

class Transact
{
public:
    Transact(const Socket& rSockP, EndPoint& rEndPointP);

    virtual ~Transact() = default;

    virtual int operator()(std::vector<uint8_t>& rBufferP) = 0;

protected:
    const Socket& rSockM;
    EndPoint& rEndPointM;
};

} /* namespace comm */
