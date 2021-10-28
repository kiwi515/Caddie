#include "caddieSceneHook.h"
#include "caddieGolfSceneHook.h"

#include "eggScene.h"

#include <Sp2Scene.h>

#include <RPSysSceneMgr.h>

#define SCENE_DISPATCH(id, func) \
    case (id): func(); break;

namespace caddie
{
    UNKTYPE * SceneHook::OnInit(UNKTYPE *obj)
    {
        RPSysSceneMgr *mgr = RPSysSceneMgr::getInstance();
        CADDIE_ASSERT(mgr != NULL);

        switch(mgr->getCurrentSceneID())
        {
            SCENE_DISPATCH(Sp2::SP2_GOLF, GolfSceneHook::OnInit);
        }

        return obj;
    }
#ifdef CADDIE_REGION_NTSC_U
    kmBranch(0x8022e7e0, &SceneHook::OnInit);
#elif CADDIE_REGION_PAL
    kmBranch(0x8022ea58, &SceneHook::OnInit);
#endif

    UNKTYPE * SceneHook::OnFrame(UNKTYPE *obj)
    {
        RPSysSceneMgr *mgr = RPSysSceneMgr::getInstance();
        CADDIE_ASSERT(mgr != NULL);

        switch(mgr->getCurrentSceneID())
        {
            SCENE_DISPATCH(Sp2::SP2_GOLF, GolfSceneHook::OnFrame);
        }

        return obj;
    }
#ifdef CADDIE_REGION_NTSC_U
    kmBranch(0x8022f8f8, &SceneHook::OnFrame);
#elif CADDIE_REGION_PAL
    kmBranch(0x8022fb70, &SceneHook::OnFrame);
#endif

    bool SceneHook::OnExit(bool b)
    {
        RPSysSceneMgr *mgr = RPSysSceneMgr::getInstance();
        CADDIE_ASSERT(mgr != NULL);

        switch(mgr->getCurrentSceneID())
        {
            SCENE_DISPATCH(Sp2::SP2_GOLF, GolfSceneHook::OnExit);
        }
        return b;
    }
#ifdef CADDIE_REGION_NTSC_U
    kmBranch(0x8022eeb0, &SceneHook::OnExit);
#elif CADDIE_REGION_PAL
    kmBranch(0x8022f128, &SceneHook::OnExit);
#endif
}