#include "caddieSceneHookMgr.hpp"

#include <RP/RPSystem.h>

namespace caddie {
namespace {

/**
 * @brief Get current scene's ID
 */
int GetCurrentSceneID() {
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
    const int scene = GetCurrentSceneID();
    const SceneHookMgr& hookMgr = SceneHookMgr::GetInstance();

    if (hookMgr.mSceneHooks[scene].onConfigure != NULL) {
        hookMgr.mSceneHooks[scene].onConfigure(GetCurrentScene());
    }

    if (hookMgr.mSharedSceneHook.onConfigure != NULL) {
        hookMgr.mSharedSceneHook.onConfigure(GetCurrentScene());
    }
}
kmBranch(0x801c389c, SceneHookMgr::DoConfigure);

/**
 * @brief Dispatch scene hook Calculate callback
 */
void SceneHookMgr::DoCalculate() {
    const int scene = GetCurrentSceneID();
    const SceneHookMgr& hookMgr = SceneHookMgr::GetInstance();

    if (hookMgr.mSceneHooks[scene].onCalculate != NULL) {
        hookMgr.mSceneHooks[scene].onCalculate(GetCurrentScene());
    }

    if (hookMgr.mSharedSceneHook.onCalculate != NULL) {
        hookMgr.mSharedSceneHook.onCalculate(GetCurrentScene());
    }
}
kmBranch(0x8022f8f8, SceneHookMgr::DoCalculate);

/**
 * @brief Dispatch scene hook UserDraw callback
 */
void SceneHookMgr::DoUserDraw() {
    const int scene = GetCurrentSceneID();
    const SceneHookMgr& hookMgr = SceneHookMgr::GetInstance();

    if (hookMgr.mSceneHooks[scene].onUserDraw != NULL) {
        hookMgr.mSceneHooks[scene].onUserDraw(GetCurrentScene());
    }

    if (hookMgr.mSharedSceneHook.onUserDraw != NULL) {
        hookMgr.mSharedSceneHook.onUserDraw(GetCurrentScene());
    }
}
kmBranch(0x802542a8, SceneHookMgr::DoUserDraw);

/**
 * @brief Dispatch scene hook Exit callback
 */
void SceneHookMgr::DoExit() {
    const int scene = GetCurrentSceneID();
    const SceneHookMgr& hookMgr = SceneHookMgr::GetInstance();

    if (hookMgr.mSceneHooks[scene].onExit != NULL) {
        hookMgr.mSceneHooks[scene].onExit(GetCurrentScene());
    }

    if (hookMgr.mSharedSceneHook.onExit != NULL) {
        hookMgr.mSharedSceneHook.onExit(GetCurrentScene());
    }
}
kmBranch(0x8022f6f4, SceneHookMgr::DoExit);

/**
 * @brief Update pause manager
 */
void SceneHookMgr::DoUpdatePause() {
    const int scene = GetCurrentSceneID();
    const SceneHookMgr& hookMgr = SceneHookMgr::GetInstance();

    if (hookMgr.mAllowPause[scene]) {
        RPSysPauseMgr::getInstance().update();
    }
}
kmCall(0x80232984, SceneHookMgr::DoUpdatePause);

} // namespace caddie
