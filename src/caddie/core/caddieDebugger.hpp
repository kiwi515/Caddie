#ifndef CADDIE_CORE_DEBUGGER_H
#define CADDIE_CORE_DEBUGGER_H
#include "types_caddie.hpp"

#include <revolution/OS.h>

namespace caddie {

/**
 * @brief Dolphin debugger utilities
 */
class Debugger {
public:
    static void Break();

private:
    static void BreakImpl();
};

} // namespace caddie

#define DEBUGGER_BREAK()                                                       \
    do {                                                                       \
        CADDIE_LOG_EX("[Debugger] break in %s! (%s:%d)", __FUNCTION__,         \
                      __FILE__, __LINE__);                                     \
        Debugger::Break();                                                     \
    } while (0)

#define DEBUGGER_BREAK_IF(expr)                                                \
    do {                                                                       \
        if (expr) {                                                            \
            CADDIE_LOG_EX("[Debugger] break in %s! (%s:%d)", __FUNCTION__,     \
                          __FILE__, __LINE__);                                 \
            Debugger::Break();                                                 \
        }                                                                      \
    } while (0)

#define DEBUGGER_PRINT_VAR(fmt, var)                                           \
    do {                                                                       \
        CADDIE_LOG_EX("[Debugger] " #var "=" fmt, var);                        \
    } while (0)

#endif
