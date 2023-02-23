#include "caddieBuildInfo.h"

#include "caddieResourceMgr.h"
#include "types_caddie.h"

namespace caddie {

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
    SetTextColor(scTextColor);
    SetPositionAbsolute(scTextPosition);

    const f32 heapFreeKb = MemManager::GetFreeSize() / 1024.0f;
    SetTextFmt("Caddie (%s, %s): %s (%.1f KB free)", GetBuildTarget(),
               GetBuildRegion(), GetBuildDate(), heapFreeKb);
}

const Vec2<f32> BuildInfo::scTextPosition(400.0f, 20.0f);
const Color BuildInfo::scTextColor(255, 0, 0, 255);

} // namespace caddie
