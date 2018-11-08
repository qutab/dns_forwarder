#include "CommandLineParser.hpp"
#include "Connection.hpp"
#include "EndPoint.hpp"
#include "Helpers.hpp"
#include "ProtocolParser.hpp"
#include "ProtocolValidator.hpp"
#include "Socket.hpp"

#include <cstring> //memset
#include <signal.h>

namespace {
const std::string LOCAL_IP("127.0.0.1");
const std::string LOCAL_PORT("9000");
} /* anonymous namespace */

void sigint_handler(int)
{
    log::logInfo("sigint received");
    exit(EXIT_SUCCESS);
}

int main(int argc, char** argv)
{
    struct sigaction action;
    std::memset(&action, 0, sizeof(struct sigaction));
    action.sa_handler = sigint_handler;
    sigaction(SIGINT, &action, NULL);

    comm::EndPoint fwdingEndPoint{LOCAL_IP, LOCAL_PORT};
    comm::Socket fwdingSock{fwdingEndPoint};

    utils::CommandLineParser cliParser{argc, argv};

    dns::ProtocolValidator validator;
    dns::ProtocolParser protocolParser;

    comm::Connection conn{fwdingSock, cliParser.getUpstreamEp(), validator};
    conn.subscribe(
        [&protocolParser, &validator](auto data)
        {
            auto prevId = protocolParser.getTransId();
            protocolParser.parse(std::move(data));
            auto newId = protocolParser.getTransId();
            validator.setId(newId);

            if (prevId != newId)
            {
                log::logInfo("Transaction ID: ");
                log::logInfo(std::hex, newId);
            }
        }
    );

    try
    {
        conn.start();
    }
    catch (const std::exception& e)
    {
        log::logError(e.what());
    }
    catch (...)
    {
        // pass
    }
    conn.stop();

    return EXIT_FAILURE;
}
