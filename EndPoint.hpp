#pragma once

#include <netinet/in.h>
#include <string>

namespace comm {

/**
 * A network endpoint identified by an IP address and a port number
 * This is a non-polymorphic class and is also copy constructible and assignable
 */
class EndPoint final
{
public:
    /** Constructs endpoint with IP @a ipAddressP and port number @a portP */
    EndPoint(std::string ipAddressP, std::string portP);

    /** Constructs endpoint with IP @a ipAddressP and port number @a portP */
    EndPoint(std::string ipAddressP, unsigned short portP);

    /** @return the internet socket address */
    sockaddr_in addr() const;

    /** Destructor */
    ~EndPoint();
private:
    sockaddr_in addrM;
};

} /* namespace comm */
