#include "caddieSceneHookMgr.h"
#include "caddieAssert.h"

#include <RPSystem/RPSysPauseMgr.h>

namespace caddie
{
    static s32 GetCurrentSceneID()
    {
        RPSysSceneMgr *mgr = RPSysSceneMgr::getInstance();
        CADDIE_ASSERT(mgr != NULL);
        return mgr->getCurrentSceneID();
    }

    static RPSysScene * GetCurrentScene()
    {
        RPSysSceneMgr *mgr = RPSysSceneMgr::getInstance();
        CADDIE_ASSERT(mgr != NULL);
        return (RPSysScene *)mgr->getCurrentScene();
    }

    void SceneHookMgr::ConfigureCallback()
    {
        s32 scene = GetCurrentSceneID();
        SceneHookMgr& hookMgr = SceneHookMgr::GetInstance();

        if (hookMgr.mSceneHooks[scene].onConfigure != NULL)
            hookMgr.mSceneHooks[scene].onConfigure(GetCurrentScene());
    }
    kmBranch(0x801c389c, SceneHookMgr::ConfigureCallback);

    void SceneHookMgr::CalculateCallback()
    {
        s32 scene = GetCurrentSceneID();
        SceneHookMgr& hookMgr = SceneHookMgr::GetInstance();

        if (hookMgr.mSceneHooks[scene].onCalculate != NULL)
            hookMgr.mSceneHooks[scene].onCalculate(GetCurrentScene());
    }
    kmBranch(0x8022f8f8, SceneHookMgr::CalculateCallback);

    void SceneHookMgr::UserDrawCallback()
    {
        s32 scene = GetCurrentSceneID();
        SceneHookMgr& hookMgr = SceneHookMgr::GetInstance();

        if (hookMgr.mSceneHooks[scene].onUserDraw != NULL)
            hookMgr.mSceneHooks[scene].onUserDraw(GetCurrentScene());
    }
    kmBranch(0x802542a8, SceneHookMgr::UserDrawCallback);

    void SceneHookMgr::ExitCallback()
    {
        s32 scene = GetCurrentSceneID();
        SceneHookMgr& hookMgr = SceneHookMgr::GetInstance();

        if (hookMgr.mSceneHooks[scene].onExit != NULL)
            hookMgr.mSceneHooks[scene].onExit(GetCurrentScene());
    }
    kmBranch(0x8022f6f4, SceneHookMgr::ExitCallback);

    void SceneHookMgr::PauseCheckCallback()
    {
        s32 scene = GetCurrentSceneID();
        SceneHookMgr& hookMgr = SceneHookMgr::GetInstance();

        if (hookMgr.mPauseSetting[scene]) {
            RPSysPauseMgr::getInstance()->update();
        }
    }
    kmCall(0x80232984, SceneHookMgr::PauseCheckCallback);
}