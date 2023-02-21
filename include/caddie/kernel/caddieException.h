#ifndef CADDIE_KERNEL_EXCEPTION_H
#define CADDIE_KERNEL_EXCEPTION_H
#include "types_caddie.h"

// Forward declaration
struct OSContext;

namespace caddie {

/**
 * @brief Caddie's exception handler
 */
class Exception {
public:
    static void InitConsole();
    static void PrintMapSymbol(void* addr);
    static void PrintContext(u32 type, const OSContext* ctx, u32 dsisr,
                             u32 dar);

private:
    static const u32 sConsoleMaxLines;
    static const char* sExceptionNames[];
};

} // namespace caddie

#endif
