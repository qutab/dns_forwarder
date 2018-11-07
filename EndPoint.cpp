#include "EndPoint.hpp"

#include "Helpers.hpp"

#include <arpa/inet.h>
#include <stdexcept>

namespace comm {

EndPoint::EndPoint(std::string ipAddressP, std::string portP)
  : EndPoint(ipAddressP, std::stoi(portP))
{
}

EndPoint::EndPoint(std::string ipAddressP, unsigned short portP)
{
    addrM.sin_family = AF_INET;
    addrM.sin_port = htons(portP);
    auto ret = inet_pton(addrM.sin_family, ipAddressP.c_str(), &addrM.sin_addr);

    err::onSystemError(ret < 0, "invalid IP address");
}

sockaddr_in EndPoint::addr() const
{
    return addrM;
}

EndPoint::~EndPoint() = default;

} /* namespace comm */
