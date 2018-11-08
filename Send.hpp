#pragma once

#include "Transact.hpp"

namespace comm {

/** A functor like object for sending data over a socket */
class Send : public Transact
{
public:
    Send(const Socket& rSockP, EndPoint& rDestP);
    ~Send() override = default;

    int operator()(std::vector<uint8_t>& rBufferP) override;

    Send(const Send&)= delete;
    Send operator=(const Send&)= delete;
};

} /* namespace comm */
