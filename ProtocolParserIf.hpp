#pragma once

#include <vector>
#include <cstdint>

namespace dns {

class ProtocolParserIf
{
public:
    virtual ~ProtocolParserIf() = default;

    virtual void parse(std::vector<uint8_t> bufferP) = 0;

    virtual uint16_t getTransId() const = 0;
};

} /* namespace dns */

