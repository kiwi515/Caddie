#ifndef CADDIE_KERNEL_DEBUG_H
#define CADDIE_KERNEL_DEBUG_H

#define STR(X) #X
#define GETSTR(X) STR(X)

#include "caddieAssert.h"

typedef void (* Func)();

#ifdef CADDIE_REGION_NTSC_U
    const Func BREAK = ((Func)0x80360ff0);
#elif CADDIE_REGION_PAL
    const Func BREAK = ((Func)0x80361310);
#endif

// Uses some random stubbed-out function that is never called
// Set a Dolphin breakpoint for this address
#ifndef NDEBUG
#define CADDIE_BREAKPOINT() do { \
    CADDIE_LOG_EX("BREAKPOINT! %s, in %s (line %d)\n", __FILE__, __FUNCTION__, __LINE__); \
    (*BREAK)(); \
} while(0)
#else
#define CADDIE_BREAKPOINT
#endif

namespace caddie
{
    void SetExceptionCallback();
}

#endif