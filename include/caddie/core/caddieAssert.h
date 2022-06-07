#ifndef CADDIE_CORE_ASSERT_H
#define CADDIE_CORE_ASSERT_H
#include "types.h"

#include <OS/OSError.h>

#ifndef NDEBUG
//! @brief Log a message to the console
#define CADDIE_LOG(msg) caddie_log(msg)

//! @brief Log a variadic message to the console
#define CADDIE_LOG_EX(msg, ...) caddie_log(msg, __VA_ARGS__)

//! @brief Log a message to the console when a condition is met
#define CADDIE_WARN(exp, msg)                                                  \
    if ((exp))                                                                 \
    CADDIE_LOG(msg)

//! @brief Log a variadic message to the console when a condition is met
#define CADDIE_WARN_EX(exp, msg, ...)                                          \
    if ((exp))                                                                 \
    CADDIE_LOG_EX(msg, __VA_ARGS__)

//! @brief Assert a condition and halt execution when it fails to hold
#define CADDIE_ASSERT(exp)                                                     \
    if (!(exp))                                                                \
    caddie_fail_assert(__FILE__, __LINE__, #exp "\n")

//! @brief Assert a condition and halt execution when it fails to hold,
//! displaying a custom error message
#define CADDIE_ASSERT_EX(exp, ...)                                             \
    if (!(exp))                                                                \
    caddie_fail_assert(__FILE__, __LINE__, __VA_ARGS__)
#else
#define CADDIE_LOG(msg)
#define CADDIE_LOG_EX(msg, ...)
#define CADDIE_WARN(exp, msg)
#define CADDIE_WARN_EX(exp, msg, ...)
#define CADDIE_ASSERT(exp, ...)
#define CADDIE_ASSERT_EX(exp, ...)
#endif

#ifdef __cplusplus
extern "C" {
#endif

void caddie_log(const char* msg, ...);
void caddie_fail_assert(const char* file, int line, const char* msg, ...);

#ifdef __cplusplus
}
#endif

#endif
