#include "caddieSharedSceneHook.hpp"

#include "caddieBuildInfo.hpp"
#include "caddieDebugger.hpp"
#include "caddieInputMgr.hpp"
#include "caddieMemoryMgr.hpp"
#include "caddieRichPresenceMgr.hpp"

namespace caddie {
namespace Shared {

/**
 * @brief Shared scene configure (enter) callback
 *
 * @param scene Current scene
 */
void SceneHook::OnConfigure(RPSysScene* scene) {
#pragma unused(scene)
    if (sBuildInfo == NULL) {
        sBuildInfo = new BuildInfo();
        CADDIE_ASSERT(sBuildInfo != NULL);
    }

    RichPresenceMgr::GetInstance().Configure();
}

/**
 * @brief Shared scene calculate callback
 *
 * @param scene Current scene
 */
void SceneHook::OnCalculate(RPSysScene* scene) {
#pragma unused(scene)
    InputMgr::GetInstance().Calculate();
}

/**
 * @brief Shared scene user draw callback
 *
 * @param scene Current scene
 */
void SceneHook::OnUserDraw(RPSysScene* scene) {
#pragma unused(scene)
    CADDIE_ASSERT(sBuildInfo != NULL);
    sBuildInfo->Calculate();
    sBuildInfo->UserDraw();
    sBuildInfo->DebugDraw();
}

BuildInfo* SceneHook::sBuildInfo = NULL;

} // namespace Shared
} // namespace caddie
