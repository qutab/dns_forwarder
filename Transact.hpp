#pragma once

#include "Socket.hpp"

#include <cstdint>
#include <vector>

namespace comm {

class Transact
{
public:
    Transact(const Socket& rSockP, EndPoint& rEndPointP, std::vector<uint8_t>& rBufferP);

    virtual ~Transact() = default;

    virtual int operator()() = 0;

protected:
    const Socket& rSockM;
    EndPoint& rEndPointM;
    std::vector<uint8_t>& rBufferM;
};

} /* namespace comm */
