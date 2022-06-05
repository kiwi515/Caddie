#include "caddieGlfSceneHook.h"
#include "caddieMapFile.h"
#include "caddieRuntime.h"
#include "caddieSceneHookMgr.h"

#include <RP/RPSystem/RPSysProjectLocal.h>
#include <egg/core/eggController.h>
#include <egg/util/eggException.h>

namespace caddie {

/**
 * @brief Mod entrypoint
 */
void main() {
    // Initialize heap
    MemManager::Initialize();

#ifndef NDEBUG
    // Always show exception handler
    static const u16 sEmptyBtnCombo[] = {0};
    EGG::Exception::setUserCallback(sEmptyBtnCombo);

    // Open symbol map
    MapFile::GetInstance().LoadFromDVD("modules/main_NTSC_U.map",
                                       MapFile::LINK_DYNAMIC);
#endif

    // Skip MotionPlus video
    RPSysProjectLocal::getInstance().setMPlusVideoSeen(true);

    // Set up Golf scene hook
    SceneHookMgr::GetInstance().SetHook(
        RPSysSceneCreator::SCENE_GLF,
        (SceneHook){GlfSceneHook::OnConfigure, GlfSceneHook::OnCalculate,
                    GlfSceneHook::OnUserDraw, GlfSceneHook::OnExit});
    // Disable pausing in the Golf scene
    SceneHookMgr::GetInstance().AllowPause(RPSysSceneCreator::SCENE_GLF, false);
}
kmBranch(0x80230b60, main);

} // namespace caddie
