#include "caddieException.h"

#include "caddieAlgorithm.h"
#include "caddieBuildInfo.h"
#include "caddieMapFile.h"

#include <egg/util.h>
#include <nw4r/db.h>

using namespace nw4r;

namespace caddie {

/**
 * @brief Initialize exception console
 * @details Purposed for increasing console max line count (32 -> 100)
 */
void Exception::InitConsole() {
    EGG::Exception::create(128, sConsoleMaxLines, 4, NULL, 1);
}
#if CADDIE_REGION_NTSC_U
kmCall(0x8022e2d4, Exception::InitConsole);
#elif CADDIE_REGION_PAL
kmCall(0x8022e54c, Exception::InitConsole);
#endif

/**
 * @brief Resolves address to a map symbol, and prints it to the exception
 * console
 * @details Prints address if symbol doesn't exist
 */
void Exception::PrintMapSymbol(void* addr) {
    const MapFile::Symbol* sym = MapFile::GetInstance().QueryTextSymbol(addr);

    if (sym != NULL) {
        // Offset into function where exception occurred
        const u32 offset =
            (sym->type == MapFile::LINK_DYNAMIC)
                ? PtrDistance(AddToPtr(GetTextStart(), sym->offset), addr)
                : PtrDistance(sym->addr, addr);
        db::Exception_Printf_("%s(+0x%04X)\n", sym->name, offset);
    } else {
        db::Exception_Printf_("%08X\n", addr);
    }
}

/**
 * @brief Prints context and build information
 * @details Overrides nw4r::db::PrintContext_
 */
void Exception::PrintContext(u32 type, const OSContext* ctx, u32 dsisr,
                             u32 dar) {
    // Exception type
    db::Exception_Printf_("******** EXCEPTION OCCURRED! ********\n");
    db::Exception_Printf_("Exception Type: %s\n", sExceptionNames[type]);

    // SRR0 (Attempt to resolve symbol)
    db::Exception_Printf_("SRR0: ");
    PrintMapSymbol(reinterpret_cast<void*>(ctx->srr0));

    // Caddie details
    db::Exception_Printf_("\n---Caddie Version---\n");
    db::Exception_Printf_("%s\n", BuildInfo::GetBuildDate());
    db::Exception_Printf_("%s (%s)\n", BuildInfo::GetBuildRegion(),
                          BuildInfo::GetBuildTarget());

    // Bug report instructions
    db::Exception_Printf_("\n---Bug Report---\n");
    db::Exception_Printf_("Use the D-Pad to scroll up/down.\n");
    db::Exception_Printf_("Please send this information in the\n");
    db::Exception_Printf_("Caddie Discord server. (#bug-report)\n");
    db::Exception_Printf_("https://discord.gg/BW23QvJaZk\n");

    // GP regs
    db::Exception_Printf_("\n---EXCEPTION_INFO_GPR---\n");
    db::Exception_Printf_("-------------------------------- GPRMAP\n");
    for (int reg = 0; reg < 10; reg++) {
        db::Exception_Printf_("R%02d:%08XH  R%02d:%08XH  R%02d:%08XH\n", reg,
                              ctx->gprs[reg], reg + 11, ctx->gprs[reg + 11],
                              reg + 22, ctx->gprs[reg + 22]);
    }
    db::Exception_Printf_("R10:%08XH  R21:%08XH\n", ctx->gprs[10],
                          ctx->gprs[21]);

    // FP regs
    db::Exception_Printf_("\n---EXCEPTION_INFO_FPR---\n");
    db::ShowFloat_(ctx);

    // Stack trace
    db::Exception_Printf_("\n---EXCEPTION_INFO_TRACE---\n");
    db::Exception_Printf_("-------------------------------- TRACE\n");
    db::Exception_Printf_("Address:   BackChain   LR save\n");
    // (At most) last 10 back chains
    u32* sp = reinterpret_cast<u32*>(ctx->gprs[1]);
    for (int i = 0; i < 10 && reinterpret_cast<uintptr_t>(sp) != 0xFFFFFFFF;
         i++) {
        // Print stack frame info
        db::Exception_Printf_("%08X:  %08X    ", sp, *sp);
        PrintMapSymbol(reinterpret_cast<void*>(sp[1]));
        sp = reinterpret_cast<u32*>(*sp);
    }
}
kmBranch(0x80166af0, Exception::PrintContext);

/**
 * @brief Max number of lines the exception console can hold
 */
const u32 Exception::sConsoleMaxLines = 100;

/**
 * @brief Table of exception names for the handler
 */
const char* Exception::sExceptionNames[] = {"System Reset",
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
