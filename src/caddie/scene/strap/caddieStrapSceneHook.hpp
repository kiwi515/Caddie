#ifndef CADDIE_SCENE_STRAP_SCENE_HOOK_H
#define CADDIE_SCENE_STRAP_SCENE_HOOK_H
#include "types_caddie.hpp"

namespace caddie {

/**
 * @brief Strap screen scene hook
 */
class StrapSceneHook {
public:
    static void OnCalculate(RPSysScene* scene);
};

} // namespace caddie

#endif
