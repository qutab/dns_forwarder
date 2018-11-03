#pragma once

//TODO: FWD Declare
#include "Socket.hpp"
#include "EndPoint.hpp"

#include <memory>

namespace comm {

/** Represents a network connection over which data can be sent and recieved */
class Connection final
{
public:
    /** @param rSockP Socket reference for the connection*/
    Connection(const Socket& rSockP);

    /**
     * @param rSockP Socket reference for the connection
     * @param rEndPointP for sending data
     */
    Connection(const Socket& rSockP, const EndPoint& rEndPointP);
    ~Connection();

    /** Receive data from remote endpoint */
    void recv();
    /** Send data to remote endpoint */
    void send();

    /** @return pointer to internal data buffer */
    uint8_t* getData();
    /** set @a pDataP as the pointer to internal data buffer*/
    void setData(uint8_t* pDataP);

    /** @return EndPoint for latest received data */
    EndPoint getLatestSender() const;

    /** Prevent copy construction and copy assignment */
    Connection(const Connection&) = delete;
    Connection& operator=(const Connection&) = delete;
public:
    class Impl;
    std::unique_ptr<Impl> pImplM;
};

} /* namespace comm */
