#include "caddieException.hpp"

#include "caddieAlgorithm.hpp"
#include "caddieBuildInfo.hpp"
#include "caddieMapFile.hpp"
#include "caddieMemoryMgr.hpp"

#include <egg/util.h>
#include <nw4r/db.h>

using namespace nw4r;

namespace caddie {
namespace {

/**
 * @brief Global context for assertion failure
 */
struct Assertion {
    const char* file;
    int line;
    const char* msg;
};

Assertion sAssertion;

} // namespace

/**
 * @brief Initialize exception console
 * @note Increases console max line count from 32
 */
void Exception::Initialize() {
    EGG::Exception::create(128, sConsoleMaxLines, 4, NULL, 1);
}
kmCall(0x8022e2d4, Exception::Initialize);

/**
 * @brief Print exception context information
 * @note Overrides nw4r::db::PrintContext_
 *
 * @param type Exception type (OSErrorType)
 * @param ctx Exception context
 * @param dsisr DSISR value
 * @param dar DAR value
 */
void Exception::PrintContext(u8 type, const OSContext* ctx, u32 dsisr,
                             u32 dar) {
#pragma unused(dsisr)
#pragma unused(dar)

    // Assertion failure simulates an exception, but with an invalid type
    if (type >= OS_ERR_MAX) {
        PrintAssert(ctx);
        return;
    }

    // Exception type
    db::Exception_Printf_("******** EXCEPTION OCCURRED! ********\n");
    db::Exception_Printf_("Exception Type: %s\n", sExceptionNames[type]);

    // SRR0 (Attempt to resolve symbol)
    db::Exception_Printf_("SRR0: ");
    PrintMapSymbol(reinterpret_cast<void*>(ctx->srr0));

    // Caddie information
    PrintCaddieInfo();

    // GP regs
    PrintGPR(ctx);

    // FP regs
    PrintFPR(ctx);

    // Stack trace
    PrintStackTrace(ctx, scExceptionTraceDepth);
}
kmBranch(0x80166af0, Exception::PrintContext);

/**
 * @brief Simulate exception on assertion failure
 *
 * @param file Assertion source file
 * @param line Assertion source line
 * @param msg Assertion message
 */
void Exception::FailAssert(const char* file, int line, const char* msg) {
    // Setup information
    sAssertion.file = file;
    sAssertion.line = line;
    sAssertion.msg = msg;

    // Simulate exception
    db::ErrorHandler_(0xFF, OSGetCurrentContext(), 0, 0);
}

/**
 * @brief Print assertion failure
 *
 * @param ctx Current context
 */
void Exception::PrintAssert(const OSContext* ctx) {
    // Assertion information
    db::Exception_Printf_("******** ASSERTION FAILED! ********\n");
    db::Exception_Printf_("%s\n", sAssertion.msg);
    db::Exception_Printf_("Source: %s(%d)\n", sAssertion.file, sAssertion.line);

    // Caddie information
    PrintCaddieInfo();

    // Stack trace
    // NOTE: Because we are not showing GPR/FPRs, there is more screen space to
    // perform a deeper stack trace
    PrintStackTrace(ctx, scAssertTraceDepth);
}

/**
 * @brief Print Caddie information to the console
 */
void Exception::PrintCaddieInfo() {
    // Caddie details
    db::Exception_Printf_("\n---Caddie Version---\n");
    db::Exception_Printf_("%s\n", BuildInfo::GetBuildDate());
    db::Exception_Printf_("%s (%s)\n", BuildInfo::GetBuildRegion(),
                          BuildInfo::GetBuildTarget());

    // Dump heap information
    db::Exception_Printf_("\n---Heap Info---\n");
    db::Exception_Printf_("Free static memory: %.1f KB\n",
                          MemoryMgr::GetInstance().GetStaticFreeSize() /
                              1024.0f);
    db::Exception_Printf_("Free scene mem: %.1f KB\n",
                          MemoryMgr::GetInstance().GetSceneFreeSize() /
                              1024.0f);

    // Bug report instructions
    db::Exception_Printf_("\n---Bug Report---\n");
    db::Exception_Printf_("Use the D-Pad to scroll up/down.\n");
    db::Exception_Printf_("Please send this information in the\n");
    db::Exception_Printf_("Caddie Discord server. (#bug-report)\n");
    db::Exception_Printf_("https://discord.gg/BW23QvJaZk\n");
}

/**
 * @brief Print GPRs to the console
 *
 * @param ctx Exception context
 */
void Exception::PrintGPR(const OSContext* ctx) {
    db::Exception_Printf_("\n---EXCEPTION_INFO_GPR---\n");
    db::Exception_Printf_("-------------------------------- GPRMAP\n");

    for (int reg = 0; reg < 10; reg++) {
        db::Exception_Printf_("R%02d:%08XH  R%02d:%08XH  R%02d:%08XH\n", reg,
                              ctx->gprs[reg], reg + 11, ctx->gprs[reg + 11],
                              reg + 22, ctx->gprs[reg + 22]);
    }

    db::Exception_Printf_("R10:%08XH  R21:%08XH\n", ctx->gprs[10],
                          ctx->gprs[21]);
}

/**
 * @brief Print FPRs to the console
 *
 * @param ctx Exception context
 */
void Exception::PrintFPR(const OSContext* ctx) {
    db::Exception_Printf_("\n---EXCEPTION_INFO_FPR---\n");
    db::ShowFloat_(ctx);
}

/**
 * @brief Print stack trace
 *
 * @param ctx Exception context
 * @param depth Trace depth
 */
void Exception::PrintStackTrace(const OSContext* ctx, int depth) {
    db::Exception_Printf_("\n---EXCEPTION_INFO_TRACE---\n");
    db::Exception_Printf_("-------------------------------- TRACE\n");
    db::Exception_Printf_("Address:   BackChain   LR save\n");

    const StackFrame* frame = reinterpret_cast<const StackFrame*>(ctx->gprs[1]);

    for (int i = 0;
         i < depth && reinterpret_cast<std::uintptr_t>(frame) != 0xFFFFFFFF;
         i++, frame = frame->next) {
        // Print stack frame info
        db::Exception_Printf_("%08X:  %08X    ", frame, frame->next);
        PrintMapSymbol(frame->lr);
    }
}

/**
 * @brief Attempt to resolve symbol by address and print it to the console
 * @details Prints as much information as possible in the event that there is no
 * corresponding symbol in the map file
 *
 * @param addr Symbol address
 */
void Exception::PrintMapSymbol(const void* addr) {
    // Symbol's offset from the start of Caddie code
    const std::ptrdiff_t textOffset = PtrDistance(GetTextStart(), addr);

    // Symbol is from WS2
    if (textOffset < 0 || textOffset >= GetTextSize()) {
        // Print raw address
        db::Exception_Printf_("%08X (WS2)\n", addr);
        return;
    }

    // Symbol is from Caddie, can we search for it in the map file?
    if (MapFile::GetInstance().IsAvailable()) {
        // Map file is available, let's use it
        const MapFile::Symbol* sym =
            MapFile::GetInstance().QueryTextSymbol(addr);

        // At this point we know the symbol is in Caddie code, so the map file
        // should always return a result. However, we do not want to make an
        // assertion to prevent the exception handler from itself throwing an
        // exception
        CADDIE_WARN_EX(sym == NULL,
                       "Caddie symbol missing(?) from link map: reloc %08X",
                       textOffset);

        // Symbol exists in map file
        if (sym != NULL) {
            // Offset into function where exception occurred
            const u32 offset =
                (sym->type == MapFile::LINK_DYNAMIC)
                    ? PtrDistance(AddToPtr(GetTextStart(), sym->offset), addr)
                    : PtrDistance(sym->addr, addr);

            // Print function name and instruction offset
            db::Exception_Printf_("%s(+0x%04X)\n", sym->name, offset);
        }
        // Caddie symbol missing from map file for some reason
        else {
            // Print raw address
            db::Exception_Printf_("%08X (CADDIE)\n", addr);
        }

        return;
    }

    /**
     * If the map file is not available, we are in one of two situations:
     * 1. The exception occurred before the map file could be read
     * 2. The map file does not exist
     *
     * Either way, we want to at least print the code's address relocatable
     * address (relative to the start of the module).
     */
    db::Exception_Printf_("%08X (RELOC)\n", textOffset);
}

const u32 Exception::sConsoleMaxLines = 100;

const char* Exception::sExceptionNames[OS_ERR_MAX] = {"System Reset",
                                                      "Machine Check",
                                                      "DSI",
                                                      "ISI",
                                                      "External Interrupt",
                                                      "Alignment",
                                                      "Program",
                                                      "Floating Point",
                                                      "Decrementer",
                                                      "System Call",
                                                      "Trace",
                                                      "Performance Monitor",
                                                      "Break Point",
                                                      "System Interrupt",
                                                      "Thermal Interrupt",
                                                      "Protection",
                                                      "Floating Point"};

} // namespace caddie
