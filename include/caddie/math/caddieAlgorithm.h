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
 * @brief Distance between two pointers
 */
static inline ptrdiff_t PtrDistance(const void* start, const void* end) {
    return reinterpret_cast<uintptr_t>(end) -
           reinterpret_cast<uintptr_t>(start);
}

/**
 * @brief Add offset to pointer
 */
static inline const void* AddToPtr(const void* ptr, s32 ofs) {
    return static_cast<const char*>(ptr) + ofs;
}

} // namespace caddie

#endif
