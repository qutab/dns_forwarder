#pragma once

#include <iostream>

namespace err {
/** Checks for system error. Throws if there is error. Prints @a pMsgP to STDERR */
void onSystemError(bool errCondP, const char* pMsgP);
} /** namespace err */

namespace log {

/** Log error */
void logError(const char* pMsgP);
/** Log warning */
void logWarn(const char* pMsgP);
/** Log info */
void logInfo(const char* pMsgP);

/** Log info. Can be used with IO manipulators */
template<typename Manip, typename Msg>
void logInfo(Manip&& rManipP, Msg&& rMsgP);

template<typename Manip, typename Msg>
void logInfo(Manip&& rManipP, Msg&& rMsgP)
{
    std::cout << "[NFO] " <<
        std::forward<decltype(rManipP)>(rManipP) <<
        std::forward<decltype(rMsgP)>(rMsgP) <<
        std::endl;
    std::cout.clear();
}

} /** namespace log */
