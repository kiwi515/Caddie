#ifndef SP2_GLF_DEFINE_H
#define SP2_GLF_DEFINE_H
#include "types.h"

namespace Sp2 {
namespace Glf {

static const u32 HOLE_MAX = 21;
static const u32 WIND_MAX = 15;
static const u32 PIN_MAX = 1;
static const u32 PLAYER_MAX = 4;

enum WindDir {
    SOUTH,
    SOUTHEAST,
    EAST,
    NORTHEAST,
    NORTH,
    NORTHWEST,
    WEST,
    SOUTHWEST,
    MAX_WIND_DIV
};

enum GameMode {
    GM_RESORT_NINE = 9,
    GM_RESORT_A = 10,
    GM_RESORT_B = 11,
    GM_RESORT_C = 12,
    GM_CLASSIC_NINE = 13,
    GM_CLASSIC_A = 14,
    GM_CLASSIC_B = 15,
    GM_CLASSIC_C = 16,
    GM_EIGHTEEN_HOLE = 17,
    GM_SPECIAL = 18
};

// Glf scene StaticMem variables
enum GlfStaticMem {
    VAR_GAMEMODE,
    VAR_NEXTHOLE,

    VAR_BLINDFLAG = 3,

    VAR_WIND = 7,
};

/**
 * @brief Pack wind into a byte for StaticMem
 */
static inline u8 PackWind(u8 direction, u8 speed) {
    return (speed << 3) | direction;
}

} // namespace Glf
} // namespace Sp2

#endif
