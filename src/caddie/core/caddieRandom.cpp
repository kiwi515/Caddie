#include "caddieRandom.hpp"

#include <revolution/OS.h>

namespace caddie {

u32 Random::sSeedHi = 0;
u32 Random::sSeedLo = 0;

/**
 * @brief Initialize seed
 */
void Random::Initialize() {
    sSeedHi = OSGetTick();
    sSeedLo = (sSeedHi >> 2) + sSeedHi;
}

/**
 * @brief Advance seed
 */
u32 Random::Calculate() {
    sSeedHi = sSeedHi * 0x41C64E6D + 0x3039;

    if (sSeedLo % 2 != 0) {
        sSeedLo = sSeedLo ^ 0x11020;
    }

    sSeedLo = sSeedLo >> 1;
    return sSeedHi ^ sSeedLo;
}

} // namespace caddie
