#ifndef SP2_UTIL_H
#define SP2_UTIL_H
#include "types_sp2.h"

namespace Sp2
{
    static const f32 sScaleDefault = 1.0f;

    void Print(const char *msg, u32 color_ARGB, bool center, f32 x, f32 y, f32 scale = sScaleDefault);

    inline void PrintOutline(const char *msg, u32 textColor, u32 outlineColor, bool center, f32 x, f32 y, f32 scale = sScaleDefault)
    {
        // Outline 
        Print(msg, outlineColor, center, x - 2.0f, y + 0.0f, scale);
        Print(msg, outlineColor, center, x + 2.0f, y + 0.0f, scale);
        Print(msg, outlineColor, center, x + 0.0f, y - 2.0f, scale);
        Print(msg, outlineColor, center, x + 0.0f, y + 2.0f, scale);

        // Text
        Print(msg, textColor, center, x, y, scale);
    }

    inline void PrintShadow(const char *msg, u32 textColor, u32 shadowColor, bool center, f32 x, f32 y, f32 scale = sScaleDefault)
    {
        // Shadow (bottom right)
        Print(msg, shadowColor, center, x + 2.0f, y + 2.0f, scale);

        // Text
        Print(msg, textColor, center, x, y, scale);
    }

    u32 UserRand(u32 *seed);
    u32 Rand();
    u32 Srand();
}

#endif