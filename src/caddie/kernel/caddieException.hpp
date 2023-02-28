#ifndef CADDIE_KERNEL_EXCEPTION_H
#define CADDIE_KERNEL_EXCEPTION_H
#include "types_caddie.hpp"

// Forward declaration
struct OSContext;

namespace caddie {

/**
 * @brief Caddie exception handler
 */
class Exception {
public:
    /**
     * @brief Codewarrior stack frame
     */
    struct StackFrame {
        const StackFrame* next;
        const void* lr;
        // . . .
    };

    // Exception stack trace depth
    static const int scExceptionTraceDepth = 10;
    // Assertion stack trace depth
    static const int scAssertTraceDepth = 20;

public:
    static void Initialize();
    static void PrintContext(u8 type, const OSContext* ctx, u32 dsisr, u32 dar);
    static void FailAssert(const char* file, int line, const char* msg);

private:
    static void PrintAssert(const OSContext* ctx);
    static void PrintCaddieInfo();
    static void PrintGPR(const OSContext* ctx);
    static void PrintFPR(const OSContext* ctx);
    static void PrintStackTrace(const OSContext* ctx, int depth);
    static void PrintMapSymbol(const void* addr);

private:
    // Max number of lines the exception console can hold
    static const u32 sConsoleMaxLines;
    // Table of exception names for the handler
    static const char* sExceptionNames[];
};

} // namespace caddie

#endif
