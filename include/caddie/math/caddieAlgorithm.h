#ifndef CADDIE_MATH_ALGORITHM_H
#define CADDIE_MATH_ALGORITHM_H
#include "types_caddie.h"

namespace caddie {

/**
 * @brief Get maximum of two values
 */
template <typename T> static inline const T& Max(const T& a, const T& b) {
    return (a < b) ? b : a;
}

/**
 * @brief Get minimum of two values
 */
template <typename T> static inline const T& Min(const T& a, const T& b) {
    return (b < a) ? b : a;
}

/**
 * @brief Distance between two pointers
 */
static inline u32 PtrDistance(const void* start, const void* end) {
    return (u32)end - (u32)start;
}

} // namespace caddie

#endif
