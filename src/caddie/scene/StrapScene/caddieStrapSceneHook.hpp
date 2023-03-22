#ifndef CADDIE_SCENE_STRAP_SCENE_HOOK_H
#define CADDIE_SCENE_STRAP_SCENE_HOOK_H
#include "types_caddie.hpp"

namespace caddie {
namespace Strap {

/**
 * @brief Strap screen scene hook
 */
class SceneHook {
public:
    static void OnCalculate(RPSysScene* scene);
};

} // namespace Strap
} // namespace caddie

#endif
