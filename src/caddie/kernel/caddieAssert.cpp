#include "caddieAssert.h"

#include "caddieColor.hpp"

#include <OS.h>
#include <cstdarg>
#include <cstdio>
#include <cstring>

namespace {

static const caddie::Color scDebugBg(0, 142, 161, 0);
static const caddie::Color scDebugFg(255, 255, 255, 0);

} // namespace

/**
 * @brief Log message to the console
 * @note Newline is automatically appended
 */
void caddie_log(const char* msg, ...) {
    // Format message
    char msg_buf[0x800];
    va_list list;
    va_start(list, msg);
    vsnprintf(msg_buf, sizeof(msg_buf), msg, list);
    va_end(list);

    OSReport("%s\n", msg_buf);
}

/**
 * @brief Halt execution and display assertion error to screen.
 * @note Overrides OSPanic
 */
void caddie_fail_assert(const char* file, int line, const char* msg, ...) {
    CADDIE_LOG("------------- HALT -------------");

    // Format message
    char msg_buf[0x800];
    va_list list;
    va_start(list, msg);
    vsnprintf(msg_buf, sizeof(msg_buf), msg, list);
    va_end(list);

    // Format full string
    char assert_buf[0x1000];
    snprintf(assert_buf, sizeof(assert_buf),
             "Assertion Failed: %s\nFile: %s(%d)", msg_buf, file, line);

    // Print to console
    CADDIE_LOG(assert_buf);
    CADDIE_LOG("Program Halt");

    // Print to screen
    OSFatal(scDebugFg, scDebugBg, assert_buf);
}
kmBranch(0x80047150, caddie_fail_assert);
