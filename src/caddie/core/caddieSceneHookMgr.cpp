#include "caddieSceneHookMgr.h"

#include "caddieAssert.h"

#include <RPSystem/RPSysPauseMgr.h>

namespace caddie {

s32 GetCurrentSceneID() {
    return RPSysSceneMgr::getInstance().getCurrentSceneID();
}

RPSysScene* GetCurrentScene() {
    return (RPSysScene*)RPSysSceneMgr::getInstance().getCurrentScene();
}

void SceneHookMgr::DoConfigure() {
    const s32 scene = GetCurrentSceneID();
    SceneHookMgr& hookMgr = SceneHookMgr::GetInstance();

    if (hookMgr.mSceneHooks[scene].onConfigure != NULL)
        hookMgr.mSceneHooks[scene].onConfigure(GetCurrentScene());
}
kmBranch(0x801c389c, SceneHookMgr::DoConfigure);

void SceneHookMgr::DoCalculate() {
    const s32 scene = GetCurrentSceneID();
    SceneHookMgr& hookMgr = SceneHookMgr::GetInstance();

    if (hookMgr.mSceneHooks[scene].onCalculate != NULL)
        hookMgr.mSceneHooks[scene].onCalculate(GetCurrentScene());
}
kmBranch(0x8022f8f8, SceneHookMgr::DoCalculate);

void SceneHookMgr::DoUserDraw() {
    const s32 scene = GetCurrentSceneID();
    SceneHookMgr& hookMgr = SceneHookMgr::GetInstance();

    if (hookMgr.mSceneHooks[scene].onUserDraw != NULL)
        hookMgr.mSceneHooks[scene].onUserDraw(GetCurrentScene());
}
kmBranch(0x802542a8, SceneHookMgr::DoUserDraw);

void SceneHookMgr::DoExit() {
    const s32 scene = GetCurrentSceneID();
    SceneHookMgr& hookMgr = SceneHookMgr::GetInstance();

    if (hookMgr.mSceneHooks[scene].onExit != NULL)
        hookMgr.mSceneHooks[scene].onExit(GetCurrentScene());
}
kmBranch(0x8022f6f4, SceneHookMgr::DoExit);

void SceneHookMgr::DoUpdatePause() {
    const s32 scene = GetCurrentSceneID();
    SceneHookMgr& hookMgr = SceneHookMgr::GetInstance();

    if (hookMgr.mPauseSetting[scene]) {
        RPSysPauseMgr::getInstance().update();
    }
}
kmCall(0x80232984, SceneHookMgr::DoUpdatePause);

} // namespace caddie
