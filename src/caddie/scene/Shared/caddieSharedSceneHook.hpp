#ifndef CADDIE_SCENE_SHARED_SCENE_HOOK_H
#define CADDIE_SCENE_SHARED_SCENE_HOOK_H
#include "types_caddie.hpp"

namespace caddie {

class BuildInfo;

/**
 * @brief Scene hook applied to all scenes (common/"shared")
 */
class SharedSceneHook {
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
