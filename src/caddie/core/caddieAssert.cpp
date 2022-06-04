#include "caddieAssert.h"

#include <OS/OSFatal.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static const u32 sDebugBg = 0x008EA1FF;
static const u32 sDebugFg = 0xFFFFFF00;

/**
 * @brief Halt execution and display assertion error to screen.
 * @note Overrides OSPanic
 * @param file Source filename
 * @param line Line containing assertion
 * @param msg Expression/message
 * @param ... Extra args
 */
void caddie_fail_assert(const char* file, int line, const char* msg, ...) {
    CADDIE_LOG("------------- HALT -------------\n");

    // Format message
    char msg_buf[0x800];
    va_list list;
    va_start(msg, list);
    vsnprintf(msg_buf, sizeof(msg_buf), msg, list);
    va_end(list);

    // Format full string
    char assert_buf[0x1000];
    snprintf(assert_buf, sizeof(assert_buf),
             "Assertion Failed: %s\nFile: %s(%d)", msg_buf, file, line);

    // Print to console
    CADDIE_LOG_EX("%s\n", assert_buf);
    CADDIE_LOG("Program Halt\n");

    // Print to screen
    OSFatal(&sDebugFg, &sDebugBg, assert_buf);
}
kmBranch(0x80047150, caddie_fail_assert);
