#include "caddieGlfSceneHook.h"
#include "caddieSceneHookMgr.h"

namespace caddie {

/**
 * @brief Mod entrypoint
 */
void main() {
    SceneHookMgr& hookMgr = SceneHookMgr::GetInstance();

    // Set up Golf scene hook
    hookMgr.SetHook(
        RPSysSceneCreator::SCENE_GLF,
        (SceneHook){GlfSceneHook::OnConfigure, GlfSceneHook::OnCalculate,
                    GlfSceneHook::OnUserDraw, GlfSceneHook::OnExit});

    // Disable pausing in the Golf scene
    hookMgr.AllowPause(RPSysSceneCreator::SCENE_GLF, false);
}
kmBranch(0x80230fc4, main);

} // namespace caddie
