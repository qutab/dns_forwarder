#pragma once

#include "ProtocolParserIf.hpp"

namespace dns {

/**
 * DNS protocol parser.
 * The parser is stateless. It expects to receive a fully formed query in its buffer.
 * The parser caches the results until a new query overwrites them.
 */
class ProtocolParser: public ProtocolParserIf
{
public:
    ProtocolParser() = default;
    virtual ~ProtocolParser() = default;

    /** @see ProtocolParserIf::parse() */
    void parse(std::vector<uint8_t> bufferP) override;

    /** @see ProtocolParserIf::getTransId() */
    uint16_t getTransId() const override;

    /** Prevent copy construction and copy assignment */
    ProtocolParser(const ProtocolParser&) = delete;
    ProtocolParser& operator=(const ProtocolParser&) = delete;

private:
    uint16_t transIdM{};
};

} /* namespace dns */
