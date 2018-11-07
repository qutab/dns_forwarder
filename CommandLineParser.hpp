#pragma once

#include <string>
#include <vector>

namespace comm {
class EndPoint;
} /* namespace comm */

namespace utils {

/** Parser for command line arguments */
class CommandLineParser final
{
public:
    /**
     * @param argc number of command line args
     * @param argv array of command line args
     */
    CommandLineParser(int argc, char* argv[]);
    ~CommandLineParser();

    /** @return upstream endpoint parsed from command line */
    comm::EndPoint getUpstreamEp() const;

private:
    std::vector<std::string> argsM;
};

} /* namespace utils */
