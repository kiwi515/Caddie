#include "caddieCmnAllSceneHook.h"

#include "caddieBuildInfo.h"
#include "caddieDebugger.h"
#include "caddieInputMgr.h"
#include "caddieResourceMgr.h"
#include "caddieRichPresenceMgr.h"

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
    ResourceMgr::GetInstance().ClearSceneCache();
    RichPresenceMgr::GetInstance().Exit();
}

BuildInfo* AllSceneHook::sBuildInfo = NULL;

} // namespace caddie
