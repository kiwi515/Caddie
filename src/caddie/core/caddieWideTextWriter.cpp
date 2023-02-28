#include "caddieWideTextWriter.hpp"

#include <RP/RPSystem.h>

namespace caddie {

WideTextWriter::WideTextWriter() {
    SetFont(RPSysFontManager::GetInstance().GetRomFont());
}

WideTextWriter::~WideTextWriter() {}

void WideTextWriter::Begin() {
    CADDIE_ASSERT(!mRendering);
    SetupGX();

    mRendering = true;
}

void WideTextWriter::End() {
    CADDIE_ASSERT(mRendering);
    mRendering = false;
}

void WideTextWriter::Printf(f32 x, f32 y, const wchar_t* msg, ...) {
    CADDIE_ASSERT(msg != NULL);

    std::va_list list;
    va_start(list, msg);

    SetCursor(x, y);
    VPrintf(msg, list);
}

} // namespace caddie
