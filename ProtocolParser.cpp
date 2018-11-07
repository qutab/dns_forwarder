#include "ProtocolParser.hpp"

#include <iostream>
#include <cstring>
#include <netinet/in.h>

#include "Helpers.hpp"

namespace dns {

void dns::ProtocolParser::parse(std::vector<uint8_t> bufferP)
{
    uint16_t transId;
    memcpy(&transId, bufferP.data(), sizeof(transId));
    transIdM = htons(transId);
    log::logInfo(std::hex, transIdM);
}

uint16_t ProtocolParser::getTransId() const
{
    return transIdM;
}

} /* namespace dns */


