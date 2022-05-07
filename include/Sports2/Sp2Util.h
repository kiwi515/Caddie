#ifndef SP2_UTIL_H
#define SP2_UTIL_H
#include "types_sp2.h"
#include <stdarg.h>

namespace Sp2
{
    void Print(const char *msg, u32 color_ARGB, bool center, f32 x, f32 y, f32 scale = 1.0f);

    static inline void Printf(f32 x, f32 y, f32 scale, u32 color, bool center, const char* msg, ...)
    {
        char msg_buf[512];
        va_list list;
        va_start(msg, list);
        vsnprintf(msg_buf, sizeof(msg_buf), msg, list);
        va_end(list);

        Print(msg_buf, color, center, x, y, scale);
    }

    static inline void PrintOutline(const char *msg, u32 textColor, u32 outlineColor, bool center, f32 x, f32 y, f32 scale = sScaleDefault)
    {
        // Outline 
        Print(msg, outlineColor, center, x - 2.0f, y + 0.0f, scale);
        Print(msg, outlineColor, center, x + 2.0f, y + 0.0f, scale);
        Print(msg, outlineColor, center, x + 0.0f, y - 2.0f, scale);
        Print(msg, outlineColor, center, x + 0.0f, y + 2.0f, scale);

        // Text
        Print(msg, textColor, center, x, y, scale);
    }

    static inline void PrintfOutline(f32 x, f32 y, f32 scale, u32 textColor, u32 outlineColor, bool center, const char* msg, ...)
    {
        char msg_buf[512];
        va_list list;
        va_start(msg, list);
        vsnprintf(msg_buf, sizeof(msg_buf), msg, list);
        va_end(list);

        PrintOutline(msg_buf, textColor, outlineColor, center, x, y, scale);
    }

    static inline void PrintShadow(const char *msg, u32 textColor, u32 shadowColor, bool center, f32 x, f32 y, f32 scale = sScaleDefault)
    {
        // Shadow (bottom right)
        Print(msg, shadowColor, center, x + 2.0f, y + 2.0f, scale);

        // Text
        Print(msg, textColor, center, x, y, scale);
    }

    static inline void PrintfShadow(f32 x, f32 y, f32 scale, u32 textColor, u32 shadowColor, bool center, const char* msg, ...)
    {
        char msg_buf[512];
        va_list list;
        va_start(msg, list);
        vsnprintf(msg_buf, sizeof(msg_buf), msg, list);
        va_end(list);

        PrintOutline(msg_buf, textColor, shadowColor, center, x, y, scale);
    }

    u32 Rand();
    u32 Srand();

    // Random number between 0 (inclusive) and max (exclusive)
    static inline u32 Rand(int max)
    {
        return Rand() % max;
    }

    // Random number between min (inclusive) and max (exclusive)
    static inline u32 Rand(int min, int max)
    {
        return Rand() % (max - min) + min;
    }
}

#endif