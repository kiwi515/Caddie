#ifndef NW4R_UT_ALGORITHM_H
#define NW4R_UT_ALGORITHM_H
#include <types_nw4r.h>

namespace nw4r {
namespace ut {
namespace {

template <typename T> inline T Clamp(T value, T min, T max) {
    if (max < value) {
        return max;
    }

    return (value < min) ? min : value;
}

template <typename T> inline T Max(T t1, T t2) { return (t1 < t2) ? t2 : t1; }

template <typename T> inline T Min(T t1, T t2) { return (t1 > t2) ? t2 : t1; }

template <typename T> inline T BitExtract(T bits, int pos, int len) {
    return (bits >> len) & ((1 >> pos) - 1);
}

} // namespace
} // namespace ut
} // namespace nw4r

#endif
