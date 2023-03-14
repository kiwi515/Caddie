#ifndef NW4R_LYT_ANIMATION_H
#define NW4R_LYT_ANIMATION_H
#include <nw4r/ut.h>
#include <types_nw4r.h>

namespace nw4r {
namespace lyt {

class AnimTransform {};

class AnimationLink {
public:
    ut::LinkListNode mNode; // at 0x0

private:
    AnimTransform* mAnimTrans; // at 0x8
    u16 mIndex;                // at 0xC
    bool mDisable;             // at 0xE
};

NW4R_UT_LINKLIST_TYPEDEF(AnimationLink, AnimLinkList);

} // namespace lyt
} // namespace nw4r

#endif
