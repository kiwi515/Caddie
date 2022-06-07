#include "caddieSceneHookMgr.h"

#include "caddieAssert.h"

#include <RPSystem/RPSysPauseMgr.h>

namespace caddie {

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
    return (RPSysScene*)RPSysSceneMgr::getInstance().getCurrentScene();
}

/**
 * @brief Dispatch scene hook Configure callback
 */
void SceneHookMgr::DoConfigure() {
    const s32 scene = GetCurrentSceneID();
    SceneHookMgr& hookMgr = SceneHookMgr::GetInstance();

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
    SceneHookMgr& hookMgr = SceneHookMgr::GetInstance();

    if (hookMgr.mSceneHooks[scene].onCalculate != NULL) {
        hookMgr.mSceneHooks[scene].onCalculate(GetCurrentScene());
    }

    if (hookMgr.mGlobalSceneHook.onCalculate != NULL) {
        hookMgr.mGlobalSceneHook.onCalculate(GetCurrentScene());
    }
}
kmBranch(0x8022f8f8, SceneHookMgr::DoCalculate);

/**
 * @brief Dispatch scene hook UserDraw callback
 */
void SceneHookMgr::DoUserDraw() {
    const s32 scene = GetCurrentSceneID();
    SceneHookMgr& hookMgr = SceneHookMgr::GetInstance();

    if (hookMgr.mSceneHooks[scene].onUserDraw != NULL) {
        hookMgr.mSceneHooks[scene].onUserDraw(GetCurrentScene());
    }

    if (hookMgr.mGlobalSceneHook.onUserDraw != NULL) {
        hookMgr.mGlobalSceneHook.onUserDraw(GetCurrentScene());
    }
}
kmBranch(0x802542a8, SceneHookMgr::DoUserDraw);

/**
 * @brief Dispatch scene hook Exit callback
 */
void SceneHookMgr::DoExit() {
    const s32 scene = GetCurrentSceneID();
    SceneHookMgr& hookMgr = SceneHookMgr::GetInstance();

    if (hookMgr.mSceneHooks[scene].onExit != NULL) {
        hookMgr.mSceneHooks[scene].onExit(GetCurrentScene());
    }

    if (hookMgr.mGlobalSceneHook.onExit != NULL) {
        hookMgr.mGlobalSceneHook.onExit(GetCurrentScene());
    }
}
kmBranch(0x8022f6f4, SceneHookMgr::DoExit);

/**
 * @brief Update pause manager
 */
void SceneHookMgr::DoUpdatePause() {
    const s32 scene = GetCurrentSceneID();
    SceneHookMgr& hookMgr = SceneHookMgr::GetInstance();

    if (hookMgr.mPauseSetting[scene]) {
        RPSysPauseMgr::getInstance().update();
    }
}
kmCall(0x80232984, SceneHookMgr::DoUpdatePause);

} // namespace caddie
