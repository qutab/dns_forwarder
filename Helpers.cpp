#include "Helpers.hpp"

#include <cassert>
#include <cstdlib>
#include <stdio.h>

namespace log {

void logSystemError(bool errCondP, const char* pErrorMsgP)
{
    if (errCondP)
    {
        perror(pErrorMsgP);
    }
}

void logError(const char* pMsgP)
{
    std::cerr << "[ERR] " << pMsgP << std::endl;
    std::cerr.clear();
}

void logWarn(const char* pMsgP)
{
    std::cerr << "[WRN] " << pMsgP << std::endl;
    std::cerr.clear();
}

void logInfo(const char* pMsgP)
{
    std::cout << "[NFO] " << pMsgP << std::endl;
    std::cout.clear();
}

} /** namespace log */
