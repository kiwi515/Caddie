#ifndef RP_SPORTS_GLF_UTILITY_H
#define RP_SPORTS_GLF_UTILITY_H
#include "types_RP.h"
#include "types_caddie.h"

#include <nw4r/math/math_types.h>

class RPGlfUtility {
public:
    static void CalcDeltaXZ(nw4r::math::VEC2& out, const nw4r::math::VEC3& v1,
                            const nw4r::math::VEC3& v2);

    static f32 CalcDeltaAngle2D(const nw4r::math::VEC2& v1,
                                const nw4r::math::VEC2& v2);
};

#endif
