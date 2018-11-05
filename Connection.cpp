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
    Impl(Transact& rTransactP)
      : rTransactM(rTransactP)
    {
        dataM.resize(RECV_BUFFER_SIZE);
    }

    void recv()
    {/*
        Receive receive{rSockM, endPointM, dataM};
        receive();

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
        Send send{rSockM, endPointM, dataM};
        send();*/
    }

    void transact()
    {
        rTransactM();
    }

    std::vector<uint8_t> getData() const
    {
        return dataM;
    }

private:
    std::vector<uint8_t> dataM;
    Transact& rTransactM;
};


Connection::Connection(Transact& rTransactP)
{
    pImplM = std::make_unique<Connection::Impl>(rTransactP);
}

Connection::~Connection() = default;

void Connection::transact()
{
    pImplM->transact();
}

std::vector<uint8_t> Connection::getData() const
{
    return pImplM->getData();
}


} /* namespace comm */
