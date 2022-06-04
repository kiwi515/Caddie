#include "caddieBuildInfo.h"

#include "types_caddie.h"

#define CADDIE_REGION_STR CADDIE_LOCALIZE("NTSC-U", "PAL", "NTSC-J", "KOR")

#ifdef NDEBUG
static const char* CADDIE_BUILD_INFO_STR =
    "Caddie (RELEASE, " CADDIE_REGION_STR "): " __DATE__ " " __TIME__;
#else
static const char* CADDIE_BUILD_INFO_STR =
    "Caddie (DEBUG, " CADDIE_REGION_STR "): " __DATE__ " " __TIME__;
#endif

namespace caddie {

using namespace nw4r;

BuildInfo::BuildInfo() {
    SetStroke(TextBox::STROKE_OUTLINE);
    SetCentered(true);
    SetTextColor(sBuildTextColor);
    SetPosition(sBuildTextPos);

    const f32 heapFreeKb = MemManager::GetFreeSize() / KB_AS_B;
    SetTextFmt("%s (%.1f KB free)\n", CADDIE_BUILD_INFO_STR, heapFreeKb);
}

const math::VEC2 BuildInfo::sBuildTextPos(400.0f, 20.0f);
const ut::Color BuildInfo::sBuildTextColor(255, 0, 0, 255);

static void ShowBuildInfo() {
    static BuildInfo text;
    text.Draw();
}
kmBranch(0x801c3490, &ShowBuildInfo);

} // namespace caddie
