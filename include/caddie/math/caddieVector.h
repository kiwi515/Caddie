#ifndef CADDIE_MATH_VECTOR_H
#define CADDIE_MATH_VECTOR_H
#include "types_caddie.h"

namespace caddie {

template <typename T> class Vec2 {
public:
    T x, y;

    Vec2() : x(T()), y(T()) {}
    Vec2(T tx, T ty) : x(tx), y(ty) {}

    f32& operator[](int i) {
        CADDIE_ASSERT(i < 2);
        return reinterpret_cast<f32*>(this)[i];
    }

    const f32& operator[](int i) const {
        CADDIE_ASSERT(i < 2);
        return reinterpret_cast<const f32*>(this)[i];
    }
};

template <typename T> class Vec3 {
public:
    T x, y, z;

    Vec3() : x(T()), y(T()), z(T()) {}
    Vec3(T tx, T ty, T tz) : x(tx), y(ty), z(tz) {}

    f32& operator[](int i) {
        CADDIE_ASSERT(i < 3);
        return reinterpret_cast<f32*>(this)[i];
    }

    const f32& operator[](int i) const {
        CADDIE_ASSERT(i < 3);
        return reinterpret_cast<const f32*>(this)[i];
    }
};

template <typename T> class Vec4 {
public:
    T x, y, z, w;

    Vec3() : x(T()), y(T()), z(T()), w(T()) {}
    Vec3(T tx, T ty, T tz, T tw) : x(tx), y(ty), z(tz), w(tw) {}

    f32& operator[](int i) {
        CADDIE_ASSERT(i < 4);
        return reinterpret_cast<f32*>(this)[i];
    }

    const f32& operator[](int i) const {
        CADDIE_ASSERT(i < 4);
        return reinterpret_cast<const f32*>(this)[i];
    }
};

} // namespace caddie

#endif
