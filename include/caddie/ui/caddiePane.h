#ifndef CADDIE_UI_PANE_H
#define CADDIE_UI_PANE_H
#include "caddieAssert.h"
#include "caddieLinkList.h"
#include "types_caddie.h"

#include <nw4r/math/math_types.h>
#include <string.h>

namespace caddie {

/**
 * @brief Base UI class
 */
class Pane {
  public:
    static u32 GetNodeOffset() { return offsetof(Pane, mNode); }

    Pane();
    virtual ~Pane();
    virtual void Draw() const;
    virtual void DrawSelf() const = 0;

    void AppendChild(Pane* child);
    void RemoveChild(const Pane* child);
    Pane* FindChild(const char* name) const;

    Pane* GetParent() const { return mParent; }
    void SetParent(Pane* p) { mParent = p; }

    bool IsVisible() const { return mIsVisible; }
    void SetVisible(bool vis) { mIsVisible = vis; }

    nw4r::math::VEC2 GetPosition() const { return mPos; }
    void SetPosition(nw4r::math::VEC2 pos) { mPos = pos; }

    const char* GetName() const { return mName; }
    void SetName(const char* str);

  public:
    //! @brief Node for intrusive list
    TLinkListNode mNode;

  protected:
    //! @brief Pane name max length
    static const int PANE_NAME_LEN = 32;

    //! @brief Parent pane
    Pane* mParent;
    //! @brief List of children
    TLinkList<Pane> mChildren;

    //! @brief Pane visibility
    bool mIsVisible;
    //! @brief Screenspace position
    nw4r::math::VEC2 mPos;

    //! @brief Pane name
    char mName[PANE_NAME_LEN + 1];
};

} // namespace caddie

#endif
