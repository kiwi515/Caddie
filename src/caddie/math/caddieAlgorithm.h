#ifndef CADDIE_MATH_ALGORITHM_H
#define CADDIE_MATH_ALGORITHM_H
#include "types_caddie.h"

namespace caddie {

/**
 * @brief Get maximum of two values
 */
template <typename T> static inline const T& Max(const T& a, const T& b) {
    return a < b ? b : a;
}

/**
 * @brief Get minimum of two values
 */
template <typename T> static inline const T& Min(const T& a, const T& b) {
    return b < a ? b : a;
}

/**
 * @brief Absolute value
 */
template <typename T> static inline T Abs(T x) { return x < 0 ? -x : x; }

/**
 * @brief Absolute value (float specialization)
 */
#ifdef __CWCC__
template <> static inline f32 Abs<f32>(register f32 x) {
    // clang-format off
    asm {
        fabs x, x
    }
    // clang-format on

    return x;
}
#endif

/**
 * @brief Distance between two pointers
 */
static inline ptrdiff_t PtrDistance(const void* start, const void* end) {
    return reinterpret_cast<uintptr_t>(end) -
           reinterpret_cast<uintptr_t>(start);
}

/**
 * @brief Add offset to pointer
 */
static inline const void* AddToPtr(const void* ptr, int ofs) {
    return static_cast<const char*>(ptr) + ofs;
}

/**
 * @brief Add offset to pointer
 */
template <typename T> static inline T* AddToPtr(const void* ptr, int ofs) {
    return reinterpret_cast<T*>(static_cast<const char*>(ptr) + ofs);
}

} // namespace caddie

#endif