#pragma once

#include "EndPoint.hpp"

#include <netinet/in.h>
#include <string>

namespace comm {

/**
 * This class created and binds a socket connection with the given EndPoint
 */
class Socket final
{
public:
    /**
     * @param rEndPointP EndPoint reference which is bound to the socket
     */
    Socket(const EndPoint& rEndPointP);
    ~Socket() = default;

    /** @return socket file descriptor via implicit conversion */
    operator int() const;

    void connect(EndPoint ep);

    /** Prevent copy construction and copy assignment */
    Socket(const Socket&) = delete;
    Socket& operator=(const Socket&) = delete;
private:
    int sockFdM;
    const EndPoint& rEndPointM;
};

} /* namespace comm */
