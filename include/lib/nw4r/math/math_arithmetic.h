#ifndef NW4R_MATH_ARITHMETIC_H
#define NW4R_MATH_ARITHMETIC_H
#include "math_types.h"
#include <OS.h>
#include <types_nw4r.h>

namespace nw4r {
namespace math {
namespace detail {

f32 FExp(f32 x);
f32 FLog(f32 x);

} // namespace detail

f32 FrSqrt(f32 x);

inline f32 FExp(f32 x) { return detail::FExp(x); }

inline f32 FLog(f32 x) {
    if (x >= 0.0f) {
        return detail::FLog(x);
    }

    return NW4R_MATH_QNAN;
}

inline f32 FSqrt(f32 x) {
    if (x < 0.0f) {
        return 0.0f;
    }

    return x * FrSqrt(x);
}

inline f32 FAbs(register f32 x) {
    // clang-format off
    asm {
        fabs x, x
    }
    // clang-format on

    return x;
}

inline f32 FSelect(register f32 val, register f32 zero, register f32 notzero) {
    // clang-format off
    asm {
        fsel zero, val, zero, notzero
    }
    // clang-format on

    return zero;
}

inline f32 U16ToF32(u16 arg) {
    f32 ret;
    OSu16tof32(&arg, &ret);
    return ret;
}

inline u16 F32ToU16(f32 arg) {
    u16 ret;
    OSf32tou16(&arg, &ret);
    return ret;
}

inline f32 S16ToF32(s16 arg) {
    f32 ret;
    OSs16tof32(&arg, &ret);
    return ret;
}

inline s16 F32ToS16(f32 arg) {
    s16 ret;
    OSf32tos16(&arg, &ret);
    return ret;
}

inline u32 F32AsU32(f32 arg) { return *reinterpret_cast<u32*>(&arg); }

inline f32 U32AsF32(u32 arg) { return *reinterpret_cast<f32*>(&arg); }

inline s32 FGetExpPart(f32 x) {
    const s32 s = F32AsU32(x);
    return ((s >> 23) & 0xFF) - 0x7F;
}

inline f32 FGetMantPart(f32 x) {
    const u32 u = F32AsU32(x);
    return U32AsF32((u & 0x807FFFFF) | 0x3F800000);
}

} // namespace math
} // namespace nw4r

#endif
