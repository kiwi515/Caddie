#include "caddieBuildInfo.hpp"

#include "caddieMemoryMgr.hpp"
#include "types_caddie.hpp"

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
}

void BuildInfo::Calculate() {
    const f32 staticFreeKb =
        MemoryMgr::GetInstance().GetStaticFreeSize() / 1024.0f;
    const f32 sceneFreeKb =
        MemoryMgr::GetInstance().GetSceneFreeSize() / 1024.0f;

    SetTextFmt(
        "Caddie (%s, %s): %s (Static free: %.1f KB, Scene free: %.1f KB)",
        GetBuildTarget(), GetBuildRegion(), GetBuildDate(), staticFreeKb,
        sceneFreeKb);
}

const Vec2<f32> BuildInfo::scTextPosition(400.0f, 20.0f);
const Color BuildInfo::scTextColor(255, 0, 0, 255);

} // namespace caddie
