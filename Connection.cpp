#include "Connection.hpp"

#include <arpa/inet.h>
#include <sys/types.h>
#include <iostream>
#include <cassert>
#include <unistd.h>
#include <cstring>
#include <sstream>
#include <vector>

#include "Receive.hpp"
#include "Send.hpp"

namespace comm {

namespace {

constexpr unsigned int RECV_BUFFER_SIZE = 549;

} // anonymous namespace

class Connection::Impl
{
public:
    Impl()
    {
    }

    void transact()
    {
    }
};

Connection::Connection(const Socket& rSockP, EndPoint sendUsP, const dns::ProtocolValidator& rValidatorP)
  : rSockM(rSockP), recvDsM("", 0), sendUsM(sendUsP), recvUsM("", 0), rValidatorM(rValidatorP)
{
    bufferM.resize(RECV_BUFFER_SIZE);
}


Connection::~Connection() = default;

void Connection::start()
{
    while (true)
    {
        eventLoop();
    }
}

void Connection::eventLoop()
{
    switch (stateM)
    {
        case State::IDLE:
            stateM = State::RECV_DS;
            break;
        case State::RECV_DS:
            stateReceiveDs();
            break;
        case State::SEND_US:
            stateSendUs();
            break;
        case State::RECV_US:
            stateReceiveUs();
            break;
        case State::SEND_DS:
            stateSendDs();
            break;
        default:
            std::cerr << "[ERR] Unknown state";
            stateM = State::IDLE;
            break;
    }
}

void Connection::stateReceiveDs()
{
    Receive recvDown{rSockM, recvDsM};
    const auto ret = transact(recvDown);
    if (ret >= 0 && !rValidatorM.isDuplicateId())
    {
        bufferM.resize(ret);
        stateM = State::SEND_US;
    }
    else
    {
        stateM = State::RECV_DS;
    }
}

void Connection::stateSendUs()
{
    Send sendUp{rSockM, sendUsM};
    const auto ret = transact(sendUp);
    if (ret >= 0)
    {
        bufferM.resize(RECV_BUFFER_SIZE);
        stateM = State::RECV_US;
    }
    else
    {
        stateM = State::RECV_DS;
    }
}

void Connection::stateReceiveUs()
{
    Receive recvUs{rSockM, recvUsM};
    const auto ret = transact(recvUs);
    const bool sameUs = (recvUsM.addr().sin_addr.s_addr == sendUsM.addr().sin_addr.s_addr);
    if (ret >= 0 && sameUs)
    {
        bufferM.resize(ret);
        stateM = State::SEND_DS;
    }
    else
    {
        stateM = State::RECV_DS;
    }
}

void Connection::stateSendDs()
{
    Send sendDs{rSockM, recvDsM};
    transact(sendDs);
    bufferM.resize(RECV_BUFFER_SIZE);
    stateM = State::RECV_DS;
}

int Connection::transact(Transact& rTransactP)
{
    auto ret = rTransactP(bufferM);
    notify();
    return ret;
}

void Connection::notify()
{
    for (auto& rFunc : callbacksM)
    {
        rFunc(bufferM);
    }
}

} /* namespace comm */

