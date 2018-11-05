#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <cassert>
#include <vector>
#include <memory>
#include <utility>

#include "Socket.hpp"
#include "Connection.hpp"
#include "EndPoint.hpp"
#include "Receive.hpp"
#include "Send.hpp"
#include "ProtocolParser.hpp"
#include "ProtocolValidator.hpp"


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

    comm::EndPoint upStreamEndPoint{upstreamIP, upstreamPort};
    dns::ProtocolValidator validator;
    dns::ProtocolParser parser;
    comm::Connection conn{fwdingSock, upStreamEndPoint, validator};
    conn.subscribe(
        [&parser, &validator](auto data)
        {
            parser.parse(std::move(data));
            validator.setId(parser.getTransId());
        }
    );

    conn.start();

    return EXIT_SUCCESS;
}
