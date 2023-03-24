#include "caddieSharedIslandType.hpp"

#include "caddieSceneCreatorEx.hpp"

#include <Sports2/Sp2StaticMem.h>
#include <revolution/OS.h>

namespace caddie {
namespace Shared {
namespace IslandType {

/**
 * @brief Determine island type using the console clock
 */
RPSysScene::IslandType GetIslandTypeFromClock() {
    OSCalendarTime cal;

    // Get time from CPU and convert to calendar time
    const s64 ticks = OSGetTime();
    OSTicksToCalendarTime(ticks, &cal);

    // Night time from 12 AM (00:00) - 7 AM (07:00)
    if (cal.hour < 7) {
        return RPSysScene::IslandType_Night;
    }

    // Daytime from 7 AM (07:00) - 5:30 PM (17:30)
    if (cal.hour < 17 || (cal.hour == 17 && cal.min < 30)) {
        return RPSysScene::IslandType_Day;
    }

    // Sunset/Evening from 5:30 PM (17:30) - 7:00 PM (19:00)
    if (cal.hour < 19) {
        return RPSysScene::IslandType_Evening;
    }

    return RPSysScene::IslandType_Night;
}

/**
 * @brief Apply island type determined from the console clock
 */
void ApplyIslandTypeFromClock() {
    const s32 scene = RPSysSceneMgr::getInstance().getCurrentSceneID();

    // Currently only the title/select scenes use this feature, as most scenes
    // don't support it
    if (scene != SceneCreatorEx::SCENE_TITLE &&
        scene != SceneCreatorEx::SCENE_MII_SELECT) {
        return;
    }

    const RPSysScene::IslandType type = GetIslandTypeFromClock();
    Sp2::StaticMem::getInstance().setIslandType(type);
}
kmBranch(0x8026a614, ApplyIslandTypeFromClock);

} // namespace IslandType
} // namespace Shared
} // namespace caddie
