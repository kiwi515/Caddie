#ifndef CADDIE_SCENE_SHARED_SCENE_HOOK_H
#define CADDIE_SCENE_SHARED_SCENE_HOOK_H
#include "types_caddie.hpp"

namespace caddie {

class BuildInfo;

namespace Shared {

/**
 * @brief Scene hook applied to all scenes (common/"shared")
 */
class SceneHook {
public:
    static void OnConfigure(RPSysScene* scene);
    static void OnCalculate(RPSysScene* scene);
    static void OnUserDraw(RPSysScene* scene);

private:
    //! @brief Build info text
    static BuildInfo* sBuildInfo;
};

} // namespace Shared
} // namespace caddie

#endif
