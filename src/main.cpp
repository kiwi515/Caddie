#include "caddieGlfSceneHook.h"
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

    // C++ static initializers
    for (StaticCtor* p = &__ctor_loc; p < &__ctor_end; p++) {
        CADDIE_ASSERT(*p != NULL);
        (*p)();
    }

    // Debug builds always show the exception handler
#ifndef NDEBUG
    static u16 sEmptyBtnCombo[] = {EGG::BTN_NONE};
    EGG::Exception::setUserCallback(sEmptyBtnCombo);
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
