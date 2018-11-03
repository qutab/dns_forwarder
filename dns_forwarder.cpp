#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <cassert>

#include "Socket.hpp"
#include "Connection.hpp"
#include "EndPoint.hpp"

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

    comm::EndPoint fwdEndPoint{"127.0.0.1", 9000};
    comm::Socket fwdSock{fwdEndPoint};
    comm::Connection fwdConn{fwdSock};
    while (true)
    {
        fwdConn.recv();
        auto originalSender = fwdConn.getLatestSender();

        comm::Connection upStreamConn{fwdSock, comm::EndPoint{upstreamIP, upstreamPort}};
        upStreamConn.setData(fwdConn.getData());
        upStreamConn.send();

        fwdConn.recv();
        comm::Connection downStreamConn{fwdSock, originalSender};
        downStreamConn.setData(fwdConn.getData());
        downStreamConn.send();
    }
    return EXIT_SUCCESS;
}
