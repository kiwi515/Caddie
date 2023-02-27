#ifndef CADDIE_UI_PANE_H
#define CADDIE_UI_PANE_H
#include "caddieLinkList.h"
#include "caddieVector.h"
#include "types_caddie.h"

namespace caddie {

/**
 * @brief Base pane (UI) class
 */
class Pane {
public:
    static u32 GetNodeOffset() { return offsetof(Pane, mNode); }

    Pane();
    virtual ~Pane();

    //! Initialize
    virtual void Configure() = 0;
    //! Load resources
    virtual void LoadResource() = 0;
    //! Reset
    virtual void Reset() = 0;
    //! Update
    virtual void Calculate() = 0;
    //! User-level recursive draw
    virtual void UserDraw() const;
    //! User-level draw self
    virtual void UserDrawSelf() const = 0;
    //! Debug-level recursive draw
    virtual void DebugDraw() const;
    //! Debug-level draw self
    virtual void DebugDrawSelf() const = 0;
    //! Terminate
    virtual void Exit() = 0;

    bool IsUserAllocated() const { return mIsUserAllocated; }
    void SetUserAllocated(bool userAlloc) { mIsUserAllocated = userAlloc; }

    void AppendChild(Pane& child);
    void RemoveChild(const Pane& child);
    Pane* FindChild(const char* name) const;

    Pane* GetParent() const { return mParent; }
    void SetParent(Pane* p) { mParent = p; }

    bool IsVisible() const { return mIsVisible; }
    void SetVisible(bool vis) { mIsVisible = vis; }

    Vec2<f32> GetPosition() const { return mPosition; }
    void SetPositionAbsolute(Vec2<f32> pos) { SetPosition(pos, POS_TYPE_ABS); }
    void SetPositionRelative(Vec2<f32> pos) { SetPosition(pos, POS_TYPE_REL); }

    const char* GetName() const { return mName; }
    void SetName(const char* str);

private:
    enum PositionType {
        POS_TYPE_ABS, //! Absolute
        POS_TYPE_REL, //! Relative to parent
    };

    void SetPosition(Vec2<f32> pos, PositionType type);

private:
    //! @brief Pane name max length
    static const int PANE_NAME_LEN = 32;

    //! @brief Node for intrusive list
    TLinkListNode mNode;

protected:
    //! @brief Whether the user must free the pane memory
    bool mIsUserAllocated;

    //! @brief Parent pane
    Pane* mParent;
    //! @brief List of children
    TLinkList<Pane> mChildren;

    //! @brief Pane visibility
    bool mIsVisible;
    //! @brief Screenspace position
    Vec2<f32> mPosition;

    //! @brief Pane name
    char mName[PANE_NAME_LEN + 1];
};

} // namespace caddie

#endif
