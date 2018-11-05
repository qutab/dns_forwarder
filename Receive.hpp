#pragma once

#include "Transact.hpp"

namespace comm {

/** A functor like object for receiving data over a socket */
class Receive : public Transact
{
public:
    Receive(const Socket& rSockP, EndPoint& rSenderP, std::vector<uint8_t>& rBufferP);
    ~Receive() = default;

    int operator()() override;

    /** Prevent copy construction and copy assignment */
    Receive(const Receive&) = delete;
    Receive& operator=(const Receive&) = delete;
};

} /* namespace comm */
