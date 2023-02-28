#include "caddieCmnAllSceneHook.hpp"

#include "caddieBuildInfo.hpp"
#include "caddieDebugger.hpp"
#include "caddieInputMgr.hpp"
#include "caddieMemoryMgr.hpp"
#include "caddieRichPresenceMgr.hpp"

namespace caddie {

/**
 * @brief All scene configure (enter) callback
 *
 * @param scene Current scene
 */
void AllSceneHook::OnConfigure(RPSysScene* scene) {
#pragma unused(scene)
    if (sBuildInfo == NULL) {
        sBuildInfo = new BuildInfo();
        CADDIE_ASSERT(sBuildInfo != NULL);
    }

    MemoryMgr::GetInstance().CreateSceneHeap();
    RichPresenceMgr::GetInstance().Configure();
}

/**
 * @brief All scene calculate callback
 *
 * @param scene Current scene
 */
void AllSceneHook::OnCalculate(RPSysScene* scene) {
#pragma unused(scene)
    InputMgr::GetInstance().Calculate();
}

/**
 * @brief All scene user draw callback
 *
 * @param scene Current scene
 */
void AllSceneHook::OnUserDraw(RPSysScene* scene) {
#pragma unused(scene)
    CADDIE_ASSERT(sBuildInfo != NULL);
    sBuildInfo->Calculate();
    sBuildInfo->UserDraw();
    sBuildInfo->DebugDraw();
}

/**
 * @brief All scene exit callback
 *
 * @param scene Current scene
 */
void AllSceneHook::OnExit(RPSysScene* scene) {
#pragma unused(scene)
    RichPresenceMgr::GetInstance().Exit();
    MemoryMgr::GetInstance().DestroySceneHeap();
}

BuildInfo* AllSceneHook::sBuildInfo = NULL;

} // namespace caddie
