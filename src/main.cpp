#include "caddieCmnAllSceneHook.hpp"
#include "caddieMapFile.hpp"
#include "caddieMemoryMgr.hpp"
#include "caddieRuntime.hpp"
#include "caddieSceneHookMgr.hpp"
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
    // Always show exception handler
    static const u16 scEmptyCombo[] = {0};
    EGG::Exception::setUserCallback(scEmptyCombo);

    // Open symbol map
    MapFile::GetInstance().LoadFromDVD("modules/main_NTSC_U.map",
                                       MapFile::LINK_DYNAMIC);
#endif

    // Skip MotionPlus video
    RPSysProjectLocal::getInstance().setMPlusVideoSeen(true);

    // All scene hook
    SceneHookMgr::GetInstance().SetHook(
        RPSysSceneCreator::SCENE_ALL,
        (SceneHook){AllSceneHook::OnConfigure, AllSceneHook::OnCalculate,
                    AllSceneHook::OnUserDraw, AllSceneHook::OnExit});

    // Strap scene hook
    SceneHookMgr::GetInstance().SetHook(
        RPSysSceneCreator::SCENE_STRAP,
        (SceneHook){NULL, StrapSceneHook::OnCalculate, NULL, NULL});
}
kmBranch(0x80230b60, main);

} // namespace caddie
