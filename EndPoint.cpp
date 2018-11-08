#include "EndPoint.hpp"

#include "Helpers.hpp"

#include <arpa/inet.h>

namespace comm {

EndPoint::EndPoint(const std::string& rIpAddressP, const std::string& rPortP)
  : EndPoint(rIpAddressP, std::stoi(rPortP))
{
}

EndPoint::EndPoint(const std::string& rIpAddressP, unsigned short portP)
{
    addrM.sin_family = AF_INET;
    addrM.sin_port = htons(portP);
    auto ret = inet_pton(addrM.sin_family, rIpAddressP.c_str(), &addrM.sin_addr);

    err::onSystemError(ret < 0, "invalid IP address");
}

sockaddr_in EndPoint::addr() const
{
    return addrM;
}

EndPoint::~EndPoint() = default;

} /* namespace comm */
