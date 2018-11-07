#include "CommandLineParser.hpp"

#include "EndPoint.hpp"
#include "Helpers.hpp"

namespace utils {

namespace {
const auto usageMsg = R"EOF(
usage: dns_forwarder server_ip server_port

dns_forwarder listens for DNS queries on UDP port localhost:9000
and forwards them to a remove server address specified via command
line arguments.
)EOF";

enum
{
    PROGNAME_INDEX = 1,
    IP_INDEX = 1,
    PORT_INDEX = 2
};
} /* anonymous namespace */

CommandLineParser::CommandLineParser(int argc, char** argv)
{
    for (int i = 0; i < argc; ++i)
    {
        argsM.emplace_back(argv[i]);
        log::logInfo(argsM.back().c_str());
    }
}

CommandLineParser::~CommandLineParser() = default;

comm::EndPoint CommandLineParser::getUpstreamEp() const
{
    try
    {
        return comm::EndPoint{argsM.at(IP_INDEX), argsM.at(PORT_INDEX)};
    }
    catch (const std::exception& e)
    {
        log::logError(e.what());
    }
    catch (...)
    {
        // pass
    }

    log::logError(usageMsg);
    std::exit(EXIT_FAILURE);

    // avoid compiler warning, program will terminate anyway
    return *static_cast<comm::EndPoint*>(nullptr);
}

} /* namespace utils */
