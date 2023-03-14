#ifndef NW4R_LYT_PANE_H
#define NW4R_LYT_PANE_H
#include "lyt_animation.h"
#include "lyt_common.h"
#include "lyt_res.h"

#include <nw4r/ut.h>
#include <types_nw4r.h>

#define NW4R_LYT_PANE_NAME_LEN 16
#define NW4R_LYT_PANE_USERDATA_LEN 8

namespace nw4r {
namespace lyt {
namespace detail {

class PaneBase {
public:
    PaneBase();
    virtual ~PaneBase(); // at 0x8

public:
    ut::LinkListNode mNode; // at 0x4
};

} // namespace detail

namespace res {

struct Pane {
    DataBlockHeader header;                    // at 0x0
    u8 flag;                                   // at 0x8
    u8 basePosition;                           // at 0x9
    u8 alpha;                                  // at 0xA
    u8 padding;                                // at 0xB
    char name[NW4R_LYT_PANE_NAME_LEN];         // at 0xC
    char userData[NW4R_LYT_PANE_USERDATA_LEN]; // at 0x1C
    math::VEC3 translate;                      // at 0x24
    math::VEC3 rotate;                         // at 0x30
    math::VEC2 scale;                          // at 0x3C
    Size size;                                 // at 0x44
};

} // namespace res

NW4R_UT_LINKLIST_TYPEDEF_EX(Pane, detail::PaneBase, PaneList);

class Pane : public detail::PaneBase {
public:
    NW4R_UT_RTTI_DECL(Pane);

    Pane(const res::Pane* block);
    virtual ~Pane();                                                // at 0x8
    virtual void CalculateMtx(const DrawInfo& info);                // at 0x10
    virtual void Draw(const DrawInfo& info);                        // at 0x14
    virtual void DrawSelf(const DrawInfo& info);                    // at 0x18
    virtual void Animate(u32 option);                               // at 0x1C
    virtual void AnimateSelf(u32 option);                           // at 0x20
    virtual ut::Color GetVtxColor(u32 index) const;                 // at 0x24
    virtual void SetVtxColor(u32 index, ut::Color color);           // at 0x28
    virtual u8 GetColorElement(u32 index) const;                    // at 0x2C
    virtual void SetColorElement(u32 index, u8 value);              // at 0x30
    virtual u8 GetVtxColorElement(u32 index) const;                 // at 0x34
    virtual void SetVtxColorElement(u32 index, u8 value);           // at 0x38
    virtual Pane* FindPaneByName(const char* name, bool recursive); // at 0x3C
    virtual Material* FindMaterialByName(const char* name,
                                         bool recursive); // at 0x40
    virtual void BindAnimation(AnimTransform* trans,
                               bool recursive); // at 0x44
    virtual void UnbindAnimation(AnimTransform* trans,
                                 bool recursive);                   // at 0x48
    virtual void UnbindAllAnimation(bool recursive);                // at 0x4C
    virtual void UnbindAnimationSelf(AnimTransform* trans);         // at 0x50
    virtual AnimationLink* FindAnimationLink(AnimTransform* trans); // at 0x54
    virtual void SetAnimationEnable(AnimTransform* trans, bool enable,
                                    bool recursive); // at 0x58
    virtual Material* GetMaterial() const;           // at 0x5C
    virtual void LoadMtx(const DrawInfo& info);      // at 0x60

    bool IsUserAllocated() const { return mUserAllocated; }

    void Init();
    void SetName(const char* name);
    void SetUserData(const char* userData);
    void AppendChild(Pane* pane);
    void InsertChild(PaneList::Iterator next, Pane* child);
    void RemoveChild(Pane* pane);
    ut::Rect GetPaneRect(const DrawInfo& info) const;

    math::VEC2 GetVtxPos() const;

protected:
    Pane* mParent;                                  // at 0xC
    PaneList mChildList;                            // at 0x10
    AnimLinkList mAnimList;                         // at 0x1C
    Material* mMaterial;                            // at 0x28
    math::VEC3 mTranslate;                          // at 0x2C
    math::VEC3 mRotate;                             // at 0x38
    math::VEC2 mScale;                              // at 0x44
    Size mSize;                                     // at 0x4C
    math::MTX34 mMtx;                               // at 0x54
    math::MTX34 mGlbMtx;                            // at 0x84
    u8 mAlpha;                                      // at 0xB4
    u8 mGlbAlpha;                                   // at 0xB5
    u8 mBasePosition;                               // at 0xB6
    u8 mFlag;                                       // at 0xB7
    char mName[NW4R_LYT_PANE_NAME_LEN + 1];         // at 0xB8
    char mUserData[NW4R_LYT_PANE_USERDATA_LEN + 1]; // at 0xC9
    bool mUserAllocated;                            // at 0xD2
};

} // namespace lyt
} // namespace nw4r

#endif
