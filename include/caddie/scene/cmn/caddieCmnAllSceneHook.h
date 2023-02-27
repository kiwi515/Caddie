#ifndef CADDIE_SCENE_CMN_ALL_SCENE_HOOK_H
#define CADDIE_SCENE_CMN_ALL_SCENE_HOOK_H
#include "types_caddie.h"

namespace caddie {

/**
 * @brief Scene hook applied to all scenes
 */
class AllSceneHook {
public:
    static void OnConfigure(RPSysScene* scene);
    static void OnCalculate(RPSysScene* scene);
    static void OnUserDraw(RPSysScene* scene);
    static void OnExit(RPSysScene* scene);

private:
    //! @brief Build info text
    static BuildInfo* sBuildInfo;
};

} // namespace caddie

#endif
