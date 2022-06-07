#include "caddieCmnGlobalSceneHook.h"

#include "caddieAssert.h"
#include "caddieBuildInfo.h"

namespace caddie {

/**
 * @brief Global scene configure (enter) callback
 *
 * @param scene Current scene
 */
void GlobalSceneHook::OnConfigure(RPSysScene* scene) {
    // Setup menu
    if (sBuildInfo == NULL) {
        sBuildInfo = new BuildInfo();
        CADDIE_ASSERT(sBuildInfo != NULL);
    }
}

/**
 * @brief Global scene calculate callback
 *
 * @param scene Current scene
 */
void GlobalSceneHook::OnCalculate(RPSysScene* scene) {}

/**
 * @brief Global scene user draw callback
 *
 * @param scene Current scene
 */
void GlobalSceneHook::OnUserDraw(RPSysScene* scene) {
    CADDIE_ASSERT(sBuildInfo != NULL);
    sBuildInfo->Draw();
}

/**
 * @brief Global scene exit callback
 *
 * @param scene Current scene
 */
void GlobalSceneHook::OnExit(RPSysScene* scene) {}

BuildInfo* GlobalSceneHook::sBuildInfo = NULL;

} // namespace caddie
