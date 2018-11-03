#include "Connection.hpp"

#include "Helpers.hpp"

#include <arpa/inet.h>
#include <sys/types.h>
#include <iostream>
#include <cassert>
#include <unistd.h>
#include <cstring>
#include <sstream>
#include <vector>


namespace comm {

namespace {

constexpr unsigned int RECV_BUFFER_SIZE = 549;

void checkTruncated(bool truncCondP)
{
    if (truncCondP)
    {
        std::cout << "[WARN] Datagram too large for buffer. Truncated." << std::endl;
    }
}

void handleData(uint8_t(&)[RECV_BUFFER_SIZE], ssize_t countP)
{
    std::cout << "Bytes received: " << countP << std::endl;
}

} // anonymous namespace

class Connection::Impl
{
public:
    Impl(const Socket& rSockP, const EndPoint& rEndPointP)
      : rSockM(rSockP), endPointM(rEndPointP)
    {
    }

    void recv()
    {
        auto addr = endPointM.addr();
        socklen_t srcAddLen = sizeof(addr);

        ssize_t count = 0;

        count = recvfrom(
                rSockM,
                dataM,
                sizeof(dataM),
                0,
                (struct sockaddr*)&addr,
                &srcAddLen);

        helpers::exitIfError(count < 0, "recvfrom failed");
        checkTruncated(count == sizeof(dataM));

        handleData(dataM, count);

        //parse requester info
        endPointM = EndPoint(inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));
        std::cout << "IP: " << inet_ntoa(addr.sin_addr) << std::endl;
        std::cout << "Port: " << ntohs(addr.sin_port) <<std::endl;

        //parse data
        //first two bytes are the id
        uint16_t id;
        std::memcpy(&id, &dataM[0], 2);

        std::stringstream stream;
        stream << std::hex << ntohs(id);
        std::string idStr(stream.str());
        std::cout << "ID: 0x" << idStr << std::endl;
    }

    void send()
    {
        auto addr = endPointM.addr();
        socklen_t addrLen = sizeof(addr);

        ssize_t count = 0;
        count = sendto(rSockM,
                getData(),
                sizeof(dataM),
                0,
                (struct sockaddr*)&addr,
                addrLen);
        helpers::exitIfError(count < 0, "send failed");
    }

    EndPoint getLatestSender() const
    {
        return endPointM;
    }

    uint8_t* getData()
    {
        return pDataM;
    }

    void setData(uint8_t* pDataP)
    {
        pDataM = pDataP;
    }

private:
    uint8_t dataM[RECV_BUFFER_SIZE];
    uint8_t* pDataM = &dataM[0];
    const Socket& rSockM;
    EndPoint endPointM;
};


Connection::Connection(const Socket& rSockP, const EndPoint& rEndPointP)
{
    pImplM = std::make_unique<Connection::Impl>(rSockP, rEndPointP);
}

Connection::Connection(const Socket& rSockP)
{
    pImplM = std::make_unique<Connection::Impl>(rSockP, EndPoint{"", 0});
}

Connection::~Connection() = default;

void Connection::recv()
{
    pImplM->recv();
}

void Connection::send()
{
    pImplM->send();
}

EndPoint Connection::getLatestSender() const
{
    return pImplM->getLatestSender();
}

uint8_t* Connection::getData()
{
    return pImplM->getData();
}

void Connection::setData(uint8_t* pDataP)
{
    return pImplM->setData(pDataP);
}

} /* namespace comm */
