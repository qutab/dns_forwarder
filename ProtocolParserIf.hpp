#pragma once

#include <vector>
#include <cstdint>

namespace dns {

/** Interface for DNS protocol parser */
class ProtocolParserIf
{
public:
    virtual ~ProtocolParserIf() = default;

    /** parse data received in @bufferP */
    virtual void parse(std::vector<uint8_t> bufferP) = 0;

    /** @return parsed transaction id from the dns query */
    virtual uint16_t getTransId() const = 0;
};

} /* namespace dns */

