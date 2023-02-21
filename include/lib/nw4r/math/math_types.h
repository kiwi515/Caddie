#ifndef NW4R_MATH_TYPES_H
#define NW4R_MATH_TYPES_H
#include <MTX.h>
#include <types_nw4r.h>

#define NW4R_MATH_QNAN (-(0.0f / 0.0f))

namespace nw4r {
namespace math {

struct _VEC2 {
    f32 x, y;
};

struct _VEC3 {
    f32 x, y, z;
};

class VEC2 : public _VEC2 {
public:
    VEC2() {}
    VEC2(f32 fx, f32 fy) {
        x = fx;
        y = fy;
    }
};

class VEC3 : public _VEC3 {
public:
    VEC3() {}
    VEC3(f32 fx, f32 fy, f32 fz) {
        x = fx;
        y = fy;
        z = fz;
    }

    operator Vec*() { return reinterpret_cast<Vec*>(this); }
    operator const Vec*() const { return reinterpret_cast<const Vec*>(this); }
};

struct _MTX33 {
    union {
        struct {
            f32 _00, _01, _02;
            f32 _10, _11, _12;
            f32 _20, _21, _22;
        };

        f32 m[3][3];
        f32 a[3 * 3];
    };
};

struct _MTX34 {
    union {
        struct {
            f32 _00, _01, _02, _03;
            f32 _10, _11, _12, _13;
            f32 _20, _21, _22, _23;
        };

        f32 m[3][4];
        f32 a[3 * 4];
        Mtx mtx;
    };
};

struct _MTX44 {
    union {
        struct {
            f32 _00, _01, _02, _03;
            f32 _10, _11, _12, _13;
            f32 _20, _21, _22, _23;
            f32 _30, _31, _32, _33;
        };

        f32 m[4][4];
        f32 a[4 * 4];
        Mtx44 mtx;
    };
};

class MTX44 : public _MTX44 {
    typedef f32 (*Mtx44Ref)[4];
    typedef const f32 (*Mtx44RefConst)[4];

public:
    MTX44() {}

    operator Mtx44Ref() { return mtx; }
    operator Mtx44RefConst() const { return mtx; }
};

class MTX33 : public _MTX33 {
public:
    MTX33() {}
};

class MTX34 : public _MTX34 {
    typedef f32 (*MtxRef)[4];
    typedef const f32 (*MtxRefConst)[4];

public:
    MTX34() {}

    operator MtxRef() { return mtx; }
    operator MtxRefConst() const { return mtx; }
};

VEC3* VEC3Maximize(VEC3* out, const VEC3* a, const VEC3* b);
VEC3* VEC3Minimize(VEC3* out, const VEC3* a, const VEC3* b);
MTX33* MTX33Identity(MTX33* mtx);
MTX33* MTX34ToMTX33(MTX33* out, const MTX34* in);
bool MTX34InvTranspose(MTX33* out, const MTX34* in);
MTX34* MTX34Zero(MTX34* mtx);
MTX34* MTX34Scale(MTX34* out, const MTX34* in, const VEC3* scale);
MTX34* MTX34Trans(MTX34* out, const MTX34* in, const VEC3* trans);
MTX34* MTX34RotAxisFIdx(MTX34* out, const VEC3* axis, f32 fidx);
MTX34* MTX34RotXYZFIdx(MTX34* out, f32 fx, f32 fy, f32 fz);
VEC3* VEC3TransformNormal(VEC3* out, const MTX34* mtx, const VEC3* vec);
MTX44* MTX44Identity(MTX44* mtx);
MTX44* MTX44Copy(MTX44* dst, const MTX44* src);

} // namespace math
} // namespace nw4r

#endif
