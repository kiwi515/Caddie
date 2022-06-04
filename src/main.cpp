#include "caddieGlfSceneHook.h"
#include "caddieSceneHookMgr.h"

#include <RP/RPSystem/RPSysProjectLocal.h>

namespace caddie {

/**
 * @brief Mod entrypoint
 */
void main() {
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
