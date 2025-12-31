#include "caddieSceneHookMgr.h"

#include <RP/RPSystem.h>

namespace caddie {
namespace {

/**
 * @brief Get current scene's ID
 */
s32 GetCurrentSceneID() {
    return RPSysSceneMgr::getInstance().getCurrentSceneID();
}

/**
 * @brief Get current scene
 */
RPSysScene* GetCurrentScene() {
    return static_cast<RPSysScene*>(
        RPSysSceneMgr::getInstance().getCurrentScene());
}

} // namespace

/**
 * @brief Dispatch scene hook Configure callback
 */
void SceneHookMgr::DoConfigure() {
    const s32 scene = GetCurrentSceneID();
    const SceneHookMgr& hookMgr = SceneHookMgr::GetInstance();

    if (hookMgr.mSceneHooks[scene].onConfigure != NULL) {
        hookMgr.mSceneHooks[scene].onConfigure(GetCurrentScene());
    }

    if (hookMgr.mGlobalSceneHook.onConfigure != NULL) {
        hookMgr.mGlobalSceneHook.onConfigure(GetCurrentScene());
    }
}
kmBranch(0x801c389c, SceneHookMgr::DoConfigure);

/**
 * @brief Dispatch scene hook Calculate callback
 */
void SceneHookMgr::DoCalculate() {
    const s32 scene = GetCurrentSceneID();
    const SceneHookMgr& hookMgr = SceneHookMgr::GetInstance();

    if (hookMgr.mSceneHooks[scene].onCalculate != NULL) {
        hookMgr.mSceneHooks[scene].onCalculate(GetCurrentScene());
    }

    if (hookMgr.mGlobalSceneHook.onCalculate != NULL) {
        hookMgr.mGlobalSceneHook.onCalculate(GetCurrentScene());
    }
}
#ifdef CADDIE_REGION_NTSC_U
kmBranch(0x8022f8f8, SceneHookMgr::DoCalculate);
#elif CADDIE_REGION_PAL
kmBranch(0x80232c64, SceneHookMgr::DoCalculate);
#endif

/**
 * @brief Dispatch scene hook UserDraw callback
 */
void SceneHookMgr::DoUserDraw() {
    const s32 scene = GetCurrentSceneID();
    const SceneHookMgr& hookMgr = SceneHookMgr::GetInstance();

    if (hookMgr.mSceneHooks[scene].onUserDraw != NULL) {
        hookMgr.mSceneHooks[scene].onUserDraw(GetCurrentScene());
    }

    if (hookMgr.mGlobalSceneHook.onUserDraw != NULL) {
        hookMgr.mGlobalSceneHook.onUserDraw(GetCurrentScene());
    }
}
#if CADDIE_REGION_NTSC_U
kmBranch(0x802542a8, SceneHookMgr::DoUserDraw);
#elif CADDIE_REGION_PAL
kmBranch(0x802545c8, SceneHookMgr::DoUserDraw);
#endif

/**
 * @brief Dispatch scene hook Exit callback
 */
void SceneHookMgr::DoExit() {
    const s32 scene = GetCurrentSceneID();
    const SceneHookMgr& hookMgr = SceneHookMgr::GetInstance();

    if (hookMgr.mSceneHooks[scene].onExit != NULL) {
        hookMgr.mSceneHooks[scene].onExit(GetCurrentScene());
    }

    if (hookMgr.mGlobalSceneHook.onExit != NULL) {
        hookMgr.mGlobalSceneHook.onExit(GetCurrentScene());
    }
}
#ifdef CADDIE_REGION_NTSC_U
kmBranch(0x8022f6f4, SceneHookMgr::DoExit);
#elif CADDIE_REGION_PAL
kmBranch(0x8022f96c, SceneHookMgr::DoExit);
#endif

/**
 * @brief Update pause manager
 */
void SceneHookMgr::DoUpdatePause() {
    const s32 scene = GetCurrentSceneID();
    const SceneHookMgr& hookMgr = SceneHookMgr::GetInstance();

    if (hookMgr.mPauseSetting[scene]) {
        RPSysPauseMgr::getInstance().update();
    }
}
#ifdef CADDIE_REGION_NTSC_U
kmCall(0x80232984, SceneHookMgr::DoUpdatePause);
#elif CADDIE_REGION_PAL
kmCall(0x80232b88, SceneHookMgr::DoUpdatePause);
#endif

} // namespace caddie
