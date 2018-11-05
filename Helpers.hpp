#pragma once

#include <stdio.h>
#include <cstdlib>

namespace log {

static void logIfError(bool errCondP, const char* pErrorMsgP)
{
    if (errCondP)
    {
        perror(pErrorMsgP);
    }
}

} /** namespace helpers */
