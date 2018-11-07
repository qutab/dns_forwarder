#pragma once

#include "PublisherAbs.hpp"

#include <memory>

namespace dns {
class ProtocolValidator;
} /* namespace dns */

namespace comm {
class EndPoint;
class Socket;

/** Represents a network connection over which data can be sent and received */
class Connection final : public utils::PublisherAbs
{
public:
    /**
     * @param rSockP socket to communicate over
     * @param sendUsP Upstream endpoint
     * @param rValidatorP Protocol validator for reporting error conditions
     */
    Connection(const Socket& rSockP, EndPoint sendUsP, const dns::ProtocolValidator& rValidatorP);

    /** virtual destructor*/
    virtual ~Connection();

    /** start the connection */
    void start();

    /** stop the connection */
    void stop();

    /** Prevent copy construction and copy assignment */
    Connection(const Connection&) = delete;
    Connection& operator=(const Connection&) = delete;
public:
    class Impl;
    std::unique_ptr<Impl> pImplM;
    /**@see utils::PublisherAbs::notify */
    void notify() override;
};

} /* namespace comm */
