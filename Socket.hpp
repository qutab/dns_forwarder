#pragma once

namespace comm {
class EndPoint;

/**
 * This class creates and binds a socket connection with the given EndPoint
 */
class Socket final
{
public:
    /**
     * @param rEndPointP EndPoint reference which is bound to the socket
     */
    explicit Socket(const EndPoint& rEndPointP);
    ~Socket();

    /** @return socket file descriptor via implicit conversion */
    operator int() const;

    /** Prevent copy construction and copy assignment */
    Socket(const Socket&) = delete;
    Socket& operator=(const Socket&) = delete;
private:
    int sockFdM;
    const EndPoint& rEndPointM;
};

} /* namespace comm */
