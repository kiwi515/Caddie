#include "caddieSharedSceneHook.hpp"

#include "caddieBuildInfo.hpp"
#include "caddieDebugger.hpp"
#include "caddieInputMgr.hpp"
#include "caddieMemoryMgr.hpp"
#include "caddieRichPresenceMgr.hpp"

namespace caddie {

/**
 * @brief Shared scene configure (enter) callback
 *
 * @param scene Current scene
 */
void SharedSceneHook::OnConfigure(RPSysScene* scene) {
#pragma unused(scene)
    if (sBuildInfo == NULL) {
        sBuildInfo = new BuildInfo();
        CADDIE_ASSERT(sBuildInfo != NULL);
    }

    MemoryMgr::GetInstance().CreateSceneHeap();
    RichPresenceMgr::GetInstance().Configure();
}

/**
 * @brief Shared scene calculate callback
 *
 * @param scene Current scene
 */
void SharedSceneHook::OnCalculate(RPSysScene* scene) {
#pragma unused(scene)
    InputMgr::GetInstance().Calculate();
}

/**
 * @brief Shared scene user draw callback
 *
 * @param scene Current scene
 */
void SharedSceneHook::OnUserDraw(RPSysScene* scene) {
#pragma unused(scene)
    CADDIE_ASSERT(sBuildInfo != NULL);
    sBuildInfo->Calculate();
    sBuildInfo->UserDraw();
    sBuildInfo->DebugDraw();
}

/**
 * @brief Shared scene exit callback
 *
 * @param scene Current scene
 */
void SharedSceneHook::OnExit(RPSysScene* scene) {
#pragma unused(scene)
    RichPresenceMgr::GetInstance().Exit();
    MemoryMgr::GetInstance().DestroySceneHeap();
}

BuildInfo* SharedSceneHook::sBuildInfo = NULL;

} // namespace caddie
