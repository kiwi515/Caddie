#ifndef CADDIE_MATH_VECTOR_H
#define CADDIE_MATH_VECTOR_H
#include "types_caddie.hpp"

#include <nw4r/math.h>

/**
 * @brief Generate index operators for vector type
 */
#define CADDIE_VEC_OP_INDEX_DEF                                                \
    f32& operator[](int i) {                                                   \
        CADDIE_ASSERT_EX(i < ARRAY_LENGTH(a), "Vector out of range.");         \
        return a[i];                                                           \
    }                                                                          \
    const f32& operator[](int i) const {                                       \
        CADDIE_ASSERT_EX(i < ARRAY_LENGTH(a), "Vector out of range.");         \
        return a[i];                                                           \
    }

namespace caddie {

template <typename T> class Vec2 {
public:
    union {
        struct {
            T x, y;
        };

        T a[2];
    };

public:
    Vec2() : x(T()), y(T()) {}
    Vec2(T tx, T ty) : x(tx), y(ty) {}

    operator nw4r::math::VEC2*() {
        return reinterpret_cast<nw4r::math::VEC2*>(this);
    }
    operator const nw4r::math::VEC2*() const {
        return reinterpret_cast<const nw4r::math::VEC2*>(this);
    }

    f32 dot() const { return x * x + y * y; }
    f32 length() const { return nw4r::math::FSqrt(dot()); }

    void normalize() {
        const f32 mag = length();
        if (mag > 0.0f) {
            const f32 mag_inv = 1.0f / mag;
            x *= mag_inv;
            y *= mag_inv;
        }
    }

    CADDIE_VEC_OP_INDEX_DEF;

    Vec2<T> operator+(const Vec2<T> rhs) const {
        return Vec2<T>(x + rhs.x, y + rhs.y);
    }
    void operator+=(const Vec2<T> rhs) {
        x += rhs.x;
        y += rhs.y;
    }

    Vec2<T> operator-(const Vec2<T> rhs) const {
        return Vec2<T>(x - rhs.x, y - rhs.y);
    }
    void operator-=(const Vec2<T> rhs) {
        x -= rhs.x;
        y -= rhs.y;
    }

    Vec2<T> operator*(f32 scalar) const {
        return Vec2<T>(x * scalar, y * scalar);
    }
    void operator*=(f32 scalar) {
        x *= scalar;
        y *= scalar;
    }

    Vec2<T> operator/(f32 scalar) const {
        return Vec2<T>(x / scalar, y / scalar);
    }
    void operator/=(f32 scalar) {
        x /= scalar;
        y /= scalar;
    }
};

template <typename T> class Vec3 {
public:
    union {
        struct {
            T x, y, z;
        };

        T a[3];
    };

    Vec3() : x(T()), y(T()), z(T()) {}
    Vec3(T tx, T ty, T tz) : x(tx), y(ty), z(tz) {}

    operator nw4r::math::VEC3*() {
        return reinterpret_cast<nw4r::math::VEC3*>(this);
    }
    operator const nw4r::math::VEC3*() const {
        return reinterpret_cast<const nw4r::math::VEC3*>(this);
    }

    f32 dot() const { return x * x + y * y + z * z; }
    f32 length() const { return nw4r::math::FSqrt(dot()); }

    void normalize() {
        const f32 mag = length();
        if (mag > 0.0f) {
            const f32 mag_inv = 1.0f / mag;
            x *= mag_inv;
            y *= mag_inv;
            z *= mag_inv;
        }
    }

    CADDIE_VEC_OP_INDEX_DEF;

    Vec3<T> operator+(const Vec3<T> rhs) const {
        return Vec3<T>(x + rhs.x, y + rhs.y, z + rhs.z);
    }
    void operator+=(const Vec3<T> rhs) {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
    }

    Vec3<T> operator-(const Vec3<T> rhs) const {
        return Vec3<T>(x - rhs.x, y - rhs.y, z - rhs.z);
    }
    void operator-=(const Vec3<T> rhs) {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
    }

    Vec3<T> operator*(f32 scalar) const {
        return Vec3<T>(x * scalar, y * scalar, z * scalar);
    }
    void operator*=(f32 scalar) {
        x *= scalar;
        y *= scalar;
        z *= scalar;
    }

    Vec3<T> operator/(f32 scalar) const {
        return Vec3<T>(x / scalar, y / scalar, z / scalar);
    }
    void operator/=(f32 scalar) {
        x /= scalar;
        y /= scalar;
        z /= scalar;
    }
};

template <typename T> class Vec4 {
public:
    union {
        struct {
            T x, y, z, w;
        };

        T a[4];
    };

    Vec4() : x(T()), y(T()), z(T()), w(T()) {}
    Vec4(T tx, T ty, T tz, T tw) : x(tx), y(ty), z(tz), w(tw) {}

    f32 dot() const { return x * x + y * y + z * z + w * w; }
    f32 length() const { return nw4r::math::FSqrt(dot()); }

    void normalize() {
        const f32 mag = length();
        if (mag > 0.0f) {
            const f32 mag_inv = 1.0f / mag;
            x *= mag_inv;
            y *= mag_inv;
            z *= mag_inv;
            w *= mag_inv;
        }
    }

    CADDIE_VEC_OP_INDEX_DEF;

    Vec4<T> operator+(const Vec4<T> rhs) const {
        return Vec4<T>(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
    }
    void operator+=(const Vec4<T> rhs) {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        w += rhs.w;
    }

    Vec4<T> operator-(const Vec4<T> rhs) const {
        return Vec4<T>(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
    }
    void operator-=(const Vec4<T> rhs) {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        w -= rhs.w;
    }

    Vec4<T> operator*(f32 scalar) const {
        return Vec4<T>(x * scalar, y * scalar, z * scalar, w * scalar);
    }
    void operator*=(f32 scalar) {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        w *= scalar;
    }

    Vec4<T> operator/(f32 scalar) const {
        return Vec3<T>(x / scalar, y / scalar, z / scalar, w / scalar);
    }
    void operator/=(f32 scalar) {
        x /= scalar;
        y /= scalar;
        z /= scalar;
        w /= scalar;
    }
};

} // namespace caddie

#endif
