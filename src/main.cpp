#include "caddieMapFile.hpp"
#include "caddieMemoryMgr.hpp"
#include "caddieRuntime.hpp"
#include "caddieSceneHookMgr.hpp"
#include "caddieSharedSceneHook.hpp"
#include "caddieStrapSceneHook.hpp"

#include <RP/RPSystem.h>
#include <egg/core.h>
#include <egg/util.h>

namespace caddie {

/**
 * @brief Mod entrypoint
 */
void main() {
#ifndef NDEBUG
    // Open symbol map
    MapFile::GetInstance().LoadFromDVD("modules/main_NTSC_U.map",
                                       MapFile::LINK_DYNAMIC);
#endif

    // Skip MotionPlus video
    RPSysProjectLocal::getInstance().setMPlusVideoSeen(true);

    // Shared scene hook
    SceneHookMgr::GetInstance().SetHook(
        RPSysSceneCreator::SCENE_SHARED,
        (SceneHook){Shared::SceneHook::OnConfigure,
                    Shared::SceneHook::OnCalculate,
                    Shared::SceneHook::OnUserDraw, NULL});

    // Strap scene hook
    SceneHookMgr::GetInstance().SetHook(
        RPSysSceneCreator::SCENE_STRAP,
        (SceneHook){NULL, Strap::SceneHook::OnCalculate, NULL, NULL});
}
kmBranch(0x80230b60, main);

} // namespace caddie
