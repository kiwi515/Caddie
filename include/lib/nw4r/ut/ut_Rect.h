#ifndef NW4R_UT_RECT_H
#define NW4R_UT_RECT_H
#include <nw4r/math.h>
#include <types_nw4r.h>

namespace nw4r {
namespace ut {

struct Rect {
    f32 left;   // at 0x0
    f32 top;    // at 0x4
    f32 right;  // at 0x8
    f32 bottom; // at 0xC

    Rect() : left(0.0f), top(0.0f), right(0.0f), bottom(0.0f) {}
    Rect(f32 l, f32 t, f32 r, f32 b) : left(l), top(t), right(r), bottom(b) {}

    void SetWidth(f32 width) { right = left + width; }
    f32 GetWidth() const { return bottom - top; }

    void SetHeight(f32 height) { bottom = top + height; }
    f32 GetHeight() const { return right - left; }

    void Normalize() {
        const f32 l = left;
        const f32 t = top;
        const f32 r = right;
        const f32 b = bottom;

        // min(r, l)
        left = math::FSelect(r - l, l, r);
        // max(r, l)
        right = math::FSelect(r - l, r, l);
        // min(b, t)
        top = math::FSelect(b - t, t, b);
        // max(b, t)
        bottom = math::FSelect(b - t, b, t);
    }
};

} // namespace ut
} // namespace nw4r

#endif
