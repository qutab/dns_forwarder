#include "ProtocolParser.hpp"

#include <iostream>
#include <cstring>
#include <netinet/in.h>

namespace dns {

void dns::ProtocolParser::parse(std::vector<uint8_t> bufferP)
{
    uint16_t transId;
    memcpy(&transId, bufferP.data(), sizeof(transId));
    std::cout << std::hex << "ID: " << htons(transId) << std::endl;
    transIdM = htons(transId);
}

uint16_t ProtocolParser::getTransId() const
{
    return transIdM;
}

} /* namespace dns */


