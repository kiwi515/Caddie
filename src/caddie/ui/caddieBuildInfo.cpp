#include "caddieBuildInfo.h"

#include "types_caddie.h"

namespace caddie {

using namespace nw4r;

/**
 * @brief Caddie module build date
 */
const char* BuildInfo::GetBuildDate() { return __DATE__ " " __TIME__; }

/**
 * @brief Caddie module build region
 */
const char* BuildInfo::GetBuildRegion() {
    return CADDIE_LOCALIZE("NTSC-U", "PAL", "NTSC-J", "KOR");
}

/**
 * @brief Caddie module build target
 */
const char* BuildInfo::GetBuildTarget() {
#ifdef NDEBUG
    return "RELEASE";
#else
    return "DEBUG";
#endif
}

BuildInfo::BuildInfo() {
    SetStroke(TextBox::STROKE_OUTLINE);
    SetCentered(true);
    SetTextColor(sBuildTextColor);
    SetPosition(sBuildTextPos);

    const f32 heapFreeKb = MemManager::GetFreeSize() / KB_AS_B;
    SetTextFmt("Caddie (%s, %s): %s (%.1f KB free)", GetBuildTarget(),
               GetBuildRegion(), GetBuildDate(), heapFreeKb);
}

const math::VEC2 BuildInfo::sBuildTextPos(400.0f, 20.0f);
const ut::Color BuildInfo::sBuildTextColor(255, 0, 0, 255);

} // namespace caddie
