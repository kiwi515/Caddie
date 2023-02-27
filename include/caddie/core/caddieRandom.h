#ifndef CADDIE_CORE_RANDOM_H
#define CADDIE_CORE_RANDOM_H
#include "types_caddie.h"

namespace caddie {

/**
 * @brief Random number generator
 */
class Random {
public:
    static void Initialize();

    // Random 32-bit integer, unbounded
    static u32 GetU32() { return Calculate(); }
    // Random 32-bit integer, specified minimum value
    static u32 GetU32(u32 max) { return GetF32() * max; }
    // Random 32-bit integer, specified range
    static u32 GetU32(u32 min, u32 max) { return GetU32(max - min) + min; }

    // Random decimal in the range [0, 1]
    static f32 GetF32() {
        const u16 randi = (GetU32() >> 16) & 0xFFFF;
        const f32 randf = static_cast<f32>(randi);
        return randf / 65536.0f;
    }

private:
    static u32 Calculate();

private:
    static u32 sSeedHi;
    static u32 sSeedLo;
};

} // namespace caddie

#endif
