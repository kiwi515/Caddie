#ifndef CADDIE_CORE_ASSERT_H
#define CADDIE_CORE_ASSERT_H
#include "types.h"

#include <OS/OSError.h>

#ifndef NDEBUG
#define CADDIE_LOG(msg) OSReport(msg)
#define CADDIE_LOG_EX(msg, ...) OSReport(msg, __VA_ARGS__)

#define CADDIE_WARN(exp, msg)                                                  \
    if ((exp))                                                                 \
    CADDIE_LOG(msg)
#define CADDIE_WARN_EX(exp, msg, ...)                                          \
    if ((exp))                                                                 \
    CADDIE_LOG(msg, __VA_ARGS__)

#define CADDIE_ASSERT(exp)                                                     \
    if (!(exp))                                                                \
    caddie_fail_assert(__FILE__, __LINE__, #exp)
#define CADDIE_ASSERT_EX(exp, msg)                                             \
    if (!(exp))                                                                \
    caddie_fail_assert(__FILE__, __LINE__, msg)
#else
#define CADDIE_LOG(msg)
#define CADDIE_LOG_EX(msg, ...)
#define CADDIE_ASSERT(exp, ...)
#define CADDIE_ASSERT_EX(exp, ...)
#endif

#ifdef __cplusplus
extern "C" {
#endif

void caddie_fail_assert(const char* file, int line, const char* msg, ...);

#ifdef __cplusplus
}
#endif

#endif
