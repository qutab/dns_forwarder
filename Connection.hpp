#pragma once

//TODO: FWD Declare
#include "Socket.hpp"
#include "EndPoint.hpp"
#include "Transact.hpp"
#include "ProtocolValidator.hpp"

#include <vector>
#include <memory>
#include <iostream>
#include <cassert>
#include <unistd.h>
#include <cstring>
#include <sstream>
#include <vector>
#include <iterator>
#include <bitset>
#include <algorithm>
#include <functional>

namespace comm {

class Publisher
{
public:
    virtual ~Publisher() = default;

    using CallBack = std::function<void(std::vector<uint8_t>)>;

    void subscribe(CallBack funcP)
    {
        callbacksM.push_back(funcP);
    }

protected:
    virtual void notify() = 0;
    std::vector<CallBack> callbacksM;
};

/** Represents a network connection over which data can be sent and received */
class Connection final : public Publisher
{
public:
    /**
     * @param rTransactP Functor for sending/receiving data
     */
    Connection(const Socket& rSockP, EndPoint sendUsP, const dns::ProtocolValidator& rValidatorP);

    virtual ~Connection();

    void start();

    /** Prevent copy construction and copy assignment */
    Connection(const Connection&) = delete;
    Connection& operator=(const Connection&) = delete;
public:
    class Impl;
    std::unique_ptr<Impl> pImplM;

    void eventLoop();

    void stateReceiveDs();
    void stateSendUs();
    void stateReceiveUs();
    void stateSendDs();

    int transact(Transact& rTransactP);
    void notify() override;

    std::vector<uint8_t> bufferM;

    enum class State
    {
        IDLE,
        RECV_DS,
        SEND_US,
        RECV_US,
        SEND_DS
    };
    State stateM{State::IDLE};
    const Socket& rSockM;

    EndPoint recvDsM;
    EndPoint sendUsM;
    EndPoint recvUsM;

    const dns::ProtocolValidator& rValidatorM;
};

} /* namespace comm */
