#include "ProtocolValidator.hpp"

namespace dns {

ProtocolValidator::ProtocolValidator() = default;

ProtocolValidator::~ProtocolValidator() = default;

void ProtocolValidator::setId(uint16_t idP)
{
    isDuplicateIdM = (idP == lastTransIdM);
    lastTransIdM = idP;
}

bool ProtocolValidator::isDuplicateId() const
{
    return isDuplicateIdM;
}

} /* namespace dns */
