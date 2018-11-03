#pragma once

#include <stdio.h>
#include <cstdlib>

namespace helpers {

static void exitIfError(bool errCondP, const char* pErrorMsgP)
{
    if (errCondP)
    {
        perror(pErrorMsgP);
        std::exit(EXIT_FAILURE);
    }
}


} /** namespace helpers */
