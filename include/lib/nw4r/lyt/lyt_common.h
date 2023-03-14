#ifndef NW4R_LYT_COMMON_H
#define NW4R_LYT_COMMON_H
#include <types_nw4r.h>

namespace nw4r {
namespace lyt {

struct Size {
    Size() : width(0.0f), height(0.0f) {}

    f32 width;  // at 0x0
    f32 height; // at 0x4
};

} // namespace lyt
} // namespace nw4r

#endif
