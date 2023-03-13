#ifndef NW4R_LYT_MATERIAL_H
#define NW4R_LYT_MATERIAL_H
#include "lyt_animation.h"
#include "lyt_res.h"
#include <types_nw4r.h>

#define TEV_COLOR_MAX 3
#define NW4R_LYT_MATERIAL_NAME_LEN 20

namespace nw4r {
namespace lyt {
namespace res {

struct Material {};

} // namespace res

namespace detail {

struct BitGXNums {
    u32 texMap : 4;
    u32 texSRT : 4;
    u32 texCoordGen : 4;
    u32 indSRT : 2;
    u32 indStage : 3;
    u32 tevSwap : 1;
    u32 tevStage : 5;
    u32 chanCtrl : 1;
    u32 matCol : 1;
    u32 alpComp : 1;
    u32 blendMode : 1;
};

} // namespace detail

class Material {
public:
    Material(const res::Material* block, const ResBlockSet& set);
    virtual ~Material();
    // TODO: Rest of virtual functions

    bool IsUserAllocated() const { return mUserAllocated; }

protected:
    AnimLinkList mAnimList;                     // at 0x4
    GXColorS10 mTevColors[TEV_COLOR_MAX];       // at 0x10
    ut::Color mTevKCols[GX_MAX_KCOLOR];         // at 0x28
    detail::BitGXNums mGXMemCap;                // at 0x38
    detail::BitGXNums mGXMemNum;                // at 0x3C
    void* mGXMem;                               // at 0x40
    char mName[NW4R_LYT_MATERIAL_NAME_LEN + 1]; // at 0x44
    bool mUserAllocated;                        // at 0x59
    u8 padding[2];                              // at 0x5A
};

} // namespace lyt
} // namespace nw4r

#endif
