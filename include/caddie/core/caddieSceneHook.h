#ifndef CADDIE_CORE_SCENE_HOOK_H
#define CADDIE_CORE_SCENE_HOOK_H
#include "types_caddie.h"
#include "types_egg.h"

namespace caddie
{
    typedef void (* SceneCallback)(RPSysScene *);
    typedef void (* PauseCallback)(RPSysScene *, bool isPause);

    struct SceneHook
    {
        SceneCallback onConfigure;
        SceneCallback onLoadResource;
        SceneCallback onCalculate;
        SceneCallback onUserDraw;
        SceneCallback onExit;
        PauseCallback onPause;
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
        static void LoadResourceCallback();
        static void CalculateCallback();
        static void UserDrawCallback();
        static void ExitCallback();
        static void PauseCallback();
        static void UnPauseCallback();

    private:
        SceneHookMgr() {}
        virtual ~SceneHookMgr() {}

    private:
        SceneHook mSceneHooks[RPSysSceneCreator::SCENE_MAX];
    };
}

#endif