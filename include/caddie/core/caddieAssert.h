#ifndef CADDIE_CORE_ASSERT_H
#define CADDIE_CORE_ASSERT_H
#include "types.h"
#include <OS/OSError.h>
#include <OS/OSFatal.h>
#include <STL/stdarg.h>
#include <STL/stdio.h>

#define CADDIE_DEBUG_BG 0x008EA1FF
#define CADDIE_DEBUG_FG 0xFFFFFF00

#ifndef NDEBUG
#define CADDIE_LOG(msg) \
    OSReport(msg)

#define CADDIE_LOG_EX(msg, ...) \
    OSReport(msg, __VA_ARGS__)

#define CADDIE_ASSERT(exp) \
    if (!(exp)) caddie::caddie_fail_assert(__FILE__, __LINE__, #exp "\n")

#define CADDIE_ASSERT_EX(exp, msg) \
    if (!(exp)) caddie::caddie_fail_assert(__FILE__, __LINE__, msg)
#else
#define CADDIE_LOG(msg)
#define CADDIE_LOG_EX(msg, ...)
#define CADDIE_ASSERT(exp, ...)
#define CADDIE_ASSERT_EX(exp, ...)
#endif

namespace caddie
{
    inline void caddie_fail_assert(const char *file, int line, const char *msg)
    {
        char buf[1024];
        sprintf(buf, "Assertion Failed: %s%s, line %d.", msg, file, line);
        
        u32 fg = CADDIE_DEBUG_FG;
        u32 bg = CADDIE_DEBUG_BG;
        OSFatal(&fg, &bg, buf);
    }
}

#endif