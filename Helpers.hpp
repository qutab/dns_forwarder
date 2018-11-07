#pragma once

#include <iostream>

namespace log {

/** Log system error if there is any */
void logSystemError(bool errCondP, const char* pErrorMsgP);
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
    std::cout <<
        std::forward<decltype(rManipP)>(rManipP) <<
        std::forward<decltype(rMsgP)>(rMsgP) <<
        std::endl;
    std::cout.clear();
}

} /** namespace log */
