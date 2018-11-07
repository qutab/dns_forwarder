#pragma once

#include <cstdint>

namespace dns {

/**
 * This class is responsible for detecting error conditions
 * based on the parsed packet fields
 */
class ProtocolValidator final
{
public:
    ProtocolValidator();
    ~ProtocolValidator();

    void setId(uint16_t idP);

    bool isDuplicateId() const;

private:
    uint16_t lastTransIdM{};
    bool isDuplicateIdM{};
};

} /* namespace dns */
