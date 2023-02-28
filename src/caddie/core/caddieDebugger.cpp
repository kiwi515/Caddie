#include "caddieDebugger.hpp"

namespace caddie {

void Debugger::Break() { BreakImpl(); }

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
