#pragma once

#include "Transact.hpp"

namespace comm {

class Send : public Transact
{
public:
    Send(const Socket& rSockP, EndPoint& rDestP, std::vector<uint8_t>& rBufferP);
    ~Send() = default;

    int operator()() override;

    Send(const Send&)= delete;
    Send operator=(const Send&)= delete;
};

} /* namespace comm */
