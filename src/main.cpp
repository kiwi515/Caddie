#include "caddieCmnGlobalSceneHook.h"
#include "caddieGlfSceneHook.h"
#include "caddieMapFile.h"
#include "caddieRuntime.h"
#include "caddieSceneHookMgr.h"

#include <RP/RPSystem.h>
#include <egg/core.h>
#include <egg/util.h>

namespace caddie {

/**
 * @brief Mod entrypoint
 */
void main() {
    // Initialize heap
    MemManager::Initialize();

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

    // Global scene hook
    SceneHookMgr::GetInstance().SetHook(
        RPSysSceneCreator::SCENE_ALL,
        (SceneHook){GlobalSceneHook::OnConfigure, GlobalSceneHook::OnCalculate,
                    GlobalSceneHook::OnUserDraw, GlobalSceneHook::OnExit});

    // Golf scene hook
    SceneHookMgr::GetInstance().SetHook(
        RPSysSceneCreator::SCENE_GLF,
        (SceneHook){GlfSceneHook::OnConfigure, GlfSceneHook::OnCalculate,
                    GlfSceneHook::OnUserDraw, GlfSceneHook::OnExit});
    // Disable pausing in the Golf scene
    SceneHookMgr::GetInstance().AllowPause(RPSysSceneCreator::SCENE_GLF, false);

    SceneHookMgr::GetInstance().SetHook(
    RPSysSceneCreator::SCENE_DGL,
    (SceneHook){GlfSceneHook::OnConfigure, GlfSceneHook::OnCalculate,
                GlfSceneHook::OnUserDraw, GlfSceneHook::OnExit});

    SceneHookMgr::GetInstance().AllowPause(RPSysSceneCreator::SCENE_DGL, false);
}
kmBranch(0x80230b60, main);

} // namespace caddie
