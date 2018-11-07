#include "Helpers.hpp"

#include <cassert>
#include <cstdlib>
#include <cstdio>

namespace err {

void onSystemError(bool errCondP, const char* pMsgP)
{
    if (errCondP)
    {
        throw std::system_error(errno, std::generic_category(), pMsgP);
    }
}

} /** namespace err */

namespace log {

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
