#ifndef CADDIE_CORE_SCENE_HOOK_MGR_H
#define CADDIE_CORE_SCENE_HOOK_MGR_H
#include "types_caddie.h"
#include "types_egg.h"

#include <RPSystem/RPSysScene.h>
#include <RPSystem/RPSysSceneMgr.h>
#include <RPSystem/RPSysSceneCreator.h>

namespace caddie
{
    typedef void (*SceneCallback)(RPSysScene*);

    struct SceneHook
    {
        SceneCallback onConfigure;
        SceneCallback onCalculate;
        SceneCallback onUserDraw;
        SceneCallback onExit;
    };

    class SceneHookMgr
    {
    public:
        static SceneHookMgr& GetInstance()
        {
            static SceneHookMgr instance;
            return instance;
        }

        void SetHook(RPSysSceneCreator::ESceneID scene, const SceneHook& hook)
        {
            mSceneHooks[scene] = hook;
        }

        static void ConfigureCallback();
        static void CalculateCallback();
        static void UserDrawCallback();
        static void ExitCallback();

    private:
        SceneHookMgr() {}
        virtual ~SceneHookMgr() {}

    private:
        SceneHook mSceneHooks[RPSysSceneCreator::SCENE_MAX];
    };
}

#endif