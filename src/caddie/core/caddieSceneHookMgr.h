#ifndef CADDIE_CORE_SCENE_HOOK_MGR_H
#define CADDIE_CORE_SCENE_HOOK_MGR_H
#include "types_caddie.h"

#include <RP/RPSystem.h>

namespace caddie {

/**
 * @brief Scene callback function pointer
 * @details Function receives pointer to current scene
 */
typedef void (*SceneCallback)(RPSysScene* scene);

/**
 * @brief Scene hook structure
 * @details Contains all callbacks for a scene
 */
struct SceneHook {
    SceneCallback onConfigure;
    SceneCallback onCalculate;
    SceneCallback onUserDraw;
    SceneCallback onExit;
};

/**
 * @brief Scene hook manager
 * @details Controls scene hooks and pause permission
 */
class SceneHookMgr {
public:
    static SceneHookMgr& GetInstance() {
        static SceneHookMgr instance;
        return instance;
    }

    void SetHook(RPSysSceneCreator::ESceneID scene, const SceneHook& hook) {
        if (scene != RPSysSceneCreator::SCENE_ALL) {
            mSceneHooks[scene] = hook;
        } else {
            mAllSceneHook = hook;
        }
    }

    void AllowPause(RPSysSceneCreator::ESceneID scene, bool pause) {
        if (scene != RPSysSceneCreator::SCENE_ALL) {
            mAllowPause[scene] = pause;
        }
    }

    static void DoConfigure();
    static void DoCalculate();
    static void DoUserDraw();
    static void DoExit();
    static void DoUpdatePause();

private:
    SceneHookMgr() {
        for (int i = 0; i < RPSysSceneCreator::SCENE_MAX; i++) {
            mAllowPause[i] = true;
        }
    }

    virtual ~SceneHookMgr() {}

private:
    //! @brief Scene hooks for every scene
    SceneHook mSceneHooks[RPSysSceneCreator::SCENE_MAX];
    //! @brief All scene hook
    SceneHook mAllSceneHook;
    //! @brief Pause permission for every scene
    bool mAllowPause[RPSysSceneCreator::SCENE_MAX];
};

} // namespace caddie

#endif
