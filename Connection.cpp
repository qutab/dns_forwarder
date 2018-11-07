#include "Connection.hpp"

#include "EndPoint.hpp"
#include "Helpers.hpp"
#include "ProtocolValidator.hpp"
#include "Receive.hpp"
#include "Send.hpp"
#include "Socket.hpp"

#include <vector>

namespace comm {

namespace {

constexpr unsigned int RECV_BUFFER_SIZE = 549;

} // anonymous namespace

/** Class to hide implementation */
class Connection::Impl
{
public:
    Impl(const Socket& rSockP,
        EndPoint sendUsP,
        const dns::ProtocolValidator& rValidatorP,
        std::vector<PublisherAbs::CallBack>& rCallbacksP)
      : rSockM(rSockP),
        recvDsM("", 0),
        sendUsM(sendUsP),
        recvUsM("", 0),
        rValidatorM(rValidatorP),
        rCallbacksM(rCallbacksP)
    {
        bufferM.resize(RECV_BUFFER_SIZE);
    }
    void start();
    void notify();

private:
    void eventLoop();

    void stateReceiveDs();
    void stateSendUs();
    void stateReceiveUs();
    void stateSendDs();

    int transact(Transact& rTransactP);

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
    std::vector<CallBack>& rCallbacksM;
};

Connection::Connection(const Socket& rSockP, EndPoint sendUsP, const dns::ProtocolValidator& rValidatorP)
  : pImplM(std::make_unique<Impl>(rSockP, sendUsP, rValidatorP, callbacksM))
{
}

Connection::~Connection() = default;

void Connection::start()
{
    pImplM->start();
}

void Connection::stop()
{
    // empty on purpose
}

void Connection::notify()
{
    pImplM->notify();
}

void Connection::Impl::start()
{
    while (true)
    {
        eventLoop();
    }
}

void Connection::Impl::eventLoop()
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
        {
            log::logError("Unknown state");
            stateM = State::IDLE;
            break;
        }
    }
}

void Connection::Impl::stateReceiveDs()
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

void Connection::Impl::stateSendUs()
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

void Connection::Impl::stateReceiveUs()
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

void Connection::Impl::stateSendDs()
{
    Send sendDs{rSockM, recvDsM};
    auto ret = transact(sendDs);
    if (ret >= 0)
    {
        log::logInfo("Handled query successfully");
    }
    bufferM.resize(RECV_BUFFER_SIZE);
    stateM = State::RECV_DS;
}

int Connection::Impl::transact(Transact& rTransactP)
{
    auto ret = rTransactP(bufferM);
    notify();
    return ret;
}

void Connection::Impl::notify()
{
    for (auto& rFunc : rCallbacksM)
    {
        rFunc(bufferM);
    }
}

} /* namespace comm */
