#include "caddieSceneHook.h"
#include "caddieGolfSceneHook.h"

#include "eggScene.h"

#include <Sp2Scene.h>

#include <RPSysSceneMgr.h>

namespace caddie
{
    UNKTYPE * SceneHook::OnInit(UNKTYPE *obj)
    {
        RPSysSceneMgr *mgr = RPSysSceneMgr::getInstance();
        CADDIE_ASSERT(mgr != NULL);

        switch(mgr->getCurrentSceneID())
        {
            case Sp2::SP2_GOLF:
                GolfSceneHook::OnInit();
                break;
        }

        return obj;
    }
    kmBranch(0x8022e7e0, &SceneHook::OnInit);

    UNKTYPE * SceneHook::OnFrame(UNKTYPE *obj)
    {
        RPSysSceneMgr *mgr = RPSysSceneMgr::getInstance();
        CADDIE_ASSERT(mgr != NULL);

        switch(mgr->getCurrentSceneID())
        {
            case Sp2::SP2_GOLF:
                GolfSceneHook::OnFrame();
                break;
        }

        return obj;
    }
    kmBranch(0x8022f8f8, &SceneHook::OnFrame);
}