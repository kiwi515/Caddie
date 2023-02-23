#include "caddieDebugger.h"

namespace caddie {

void Debugger::Break() { BreakImpl(); }

void Debugger::BreakIf(bool expr) {
    if (expr) {
        Break();
    }
}

asm void Debugger::BreakImpl() {
    // clang-format off
    fralloc
    sync

    bl OSDisableInterrupts

loop:
    nop
    b loop

    bl OSEnableInterrupts

    frfree
    blr
    // clang-format on
}

} // namespace caddie
