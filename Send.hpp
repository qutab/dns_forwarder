#pragma once

#include "Transact.hpp"

namespace comm {

class Send : public Transact
{
public:
    Send(const Socket& rSockP, EndPoint& rDestP);
    ~Send() = default;

    int operator()(std::vector<uint8_t>& rBufferP) override;

    Send(const Send&)= delete;
    Send operator=(const Send&)= delete;
};

} /* namespace comm */
