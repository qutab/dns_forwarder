#pragma once

#include "ProtocolParserIf.hpp"

namespace dns {

class ProtocolParser: public ProtocolParserIf
{
public:
    virtual ~ProtocolParser() = default;

    void parse(std::vector<uint8_t> bufferP) override;

    uint16_t getTransId() const override;

private:
    uint16_t transIdM;
};

} /* namespace dns */
