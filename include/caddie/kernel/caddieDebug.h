#ifndef CADDIE_KERNEL_DEBUG_H
#define CADDIE_KERNEL_DEBUG_H

#define STR(X) #X
#define GETSTR(X) STR(X)

#include "caddieAssert.h"

typedef void (* Func)();
// Uses some random stubbed-out function that is never called
// Set a Dolphin breakpoint for this address
#ifndef NDEBUG
#define CADDIE_BREAKPOINT do { CADDIE_LOG("BREAKPOINT! " __FILE__ " " GETSTR(__LINE__)); (*((Func)0x80360ff0))(); } while(0)
#else
#define CADDIE_BREAKPOINT
#endif

#endif