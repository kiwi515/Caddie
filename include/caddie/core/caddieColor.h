#ifndef CADDIE_CORE_COLOR_H
#define CADDIE_CORE_COLOR_H
#include "types_caddie.h"

namespace caddie {

/**
 * @brief 32-bit, RGBA color
 */
class Color {
public:
    u8 r, g, b, a;

    Color() : r(255), g(255), b(255), a(255) {}
    Color(int red, int green, int blue, int alpha) {
        r = red;
        g = green;
        b = blue;
        a = alpha;
    }

    u32 ToARGB() const { return (a << 24) | (r << 16) | (g << 8) | (b); }
    u32 ToRGBA() { return (r << 24) | (g << 16) | (b << 8) | (a); }

    operator nw4r::ut::Color*() {
        return reinterpret_cast<nw4r::ut::Color*>(this);
    }
    operator const nw4r::ut::Color*() const {
        return reinterpret_cast<const nw4r::ut::Color*>(this);
    }
};

} // namespace caddie

#endif
