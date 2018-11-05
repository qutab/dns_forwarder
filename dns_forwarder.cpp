#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <cassert>
#include <vector>
#include <memory>

#include "Socket.hpp"
#include "Connection.hpp"
#include "EndPoint.hpp"
#include "Receive.hpp"
#include "Send.hpp"

void sigint_handler(int)
{
    std::cout << "sigterm received" << std::endl;
    exit(EXIT_SUCCESS);
}

int main(int argc, char** argv)
{
    struct sigaction action;
    memset(&action, 0, sizeof(struct sigaction));
    action.sa_handler = sigint_handler;
    sigaction(SIGINT, &action, NULL);

    std::cout << argc << std::endl;
    std::cout << argv[1] << std::endl;
    std::cout << argv[2] << std::endl;
    assert(std::cout.good());

    std::string upstreamIP(argv[1]);
    std::string upstreamPort(argv[2]);

    comm::EndPoint fwdingEndPoint{"127.0.0.1", 9000};
    comm::Socket fwdingSock{fwdingEndPoint};

    while (true)
    {
        std::vector<uint8_t> buffer(549);

        // Receive from downstream
        comm::EndPoint downStreamEndPoint{"", 0};
        comm::Receive recvDown{fwdingSock, downStreamEndPoint, buffer};
        comm::Connection connRecvDown{recvDown};
        connRecvDown.transact();

        // Forward to upstream
        comm::EndPoint upstrEndPoint{upstreamIP, upstreamPort};
        comm::Send sendUp{fwdingSock, upstrEndPoint, buffer};
        comm::Connection connSendUp{sendUp};
        connSendUp.transact();

        //re-use the same buffer
        buffer.resize(549);

        // Receive response from upstream
        comm::EndPoint upStreamEndPoint{"", 0};
        comm::Receive recvUp{fwdingSock, upStreamEndPoint, buffer};
        comm::Connection connRecvUp{recvUp};
        connRecvUp.transact();

        // Send response to downstream
        comm::Send sendDown{fwdingSock, downStreamEndPoint, buffer};
        comm::Connection connSendDown{sendDown};
        connSendDown.transact();
    }

    return EXIT_SUCCESS;
}
