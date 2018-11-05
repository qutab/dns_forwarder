#pragma once

//TODO: FWD Declare
#include "Socket.hpp"
#include "EndPoint.hpp"
#include "Transact.hpp"

#include <vector>
#include <memory>

namespace comm {

/** Represents a network connection over which data can be sent and received */
class Connection final
{
public:
    /**
     * @param rSockP Socket reference for the connection
     * @param rEndPointP for sending/receiving data
     */
    Connection(Transact& rTransactP);
    ~Connection();

    void transact();

    /** @return data buffer */
    std::vector<uint8_t> getData() const;

    /** Prevent copy construction and copy assignment */
    Connection(const Connection&) = delete;
    Connection& operator=(const Connection&) = delete;
public:
    class Impl;
    std::unique_ptr<Impl> pImplM;
};

} /* namespace comm */
