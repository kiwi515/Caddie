#ifndef CADDIE_SCENE_DEBUG_ROOT_H
#define CADDIE_SCENE_DEBUG_ROOT_H
#include "types_caddie.hpp"

#include <RP/RPSystem.h>

namespace caddie {
namespace DebugRoot {

class Scene : public RPSysScene {
public:
    Scene() {}
    virtual ~Scene() {}

    virtual void Calculate();
    virtual void UserDraw();
};

} // namespace DebugRoot
} // namespace caddie

#endif
