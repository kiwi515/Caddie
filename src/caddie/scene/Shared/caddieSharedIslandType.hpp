#ifndef CADDIE_SCENE_SHARED_ISLAND_TYPE_H
#define CADDIE_SCENE_SHARED_ISLAND_TYPE_H
#include "types_caddie.hpp"

#include <RP/RPSystem.h>

namespace caddie {
namespace Shared {
namespace IslandType {

RPSysScene::IslandType GetIslandTypeFromClock();
void ApplyIslandTypeFromClock();

} // namespace IslandType
} // namespace Shared
} // namespace caddie

#endif
