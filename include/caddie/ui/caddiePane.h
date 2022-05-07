#ifndef CADDIE_UI_PANE_H
#define CADDIE_UI_PANE_H
#include "types_caddie.h"
#include "caddieTLinkList.h"
#include "math_types.h"

namespace caddie
{
    class Pane
    {
    public:
        Pane();
        virtual ~Pane();
        virtual void Draw() = 0;
        virtual Pane* FindChild(const char *name);

        void AddChild(Pane *child);
        void RemoveChild(Pane *child);

        Pane* GetParent() const { return mParent; }
        void SetParent(Pane* p) { mParent = p; }

        nw4r::math::VEC2 GetPosition() const { return mPos; }
        void SetPosition(const nw4r::math::VEC2& pos) { mPos = pos; }

        nw4r::math::VEC2 GetScale() const { return mScale; }
        void SetScale(const nw4r::math::VEC2& scale) { mScale = scale; }

    public:
        TLinkListNode mNode;
        typedef TLinkList<Pane, offsetof(Pane, mNode)> PaneList;
        typedef PaneList::Iterator PaneIterator;

    private:
        static const int NAME_LENGTH = 16;

        Pane* mParent;
        PaneList mChildren;

        nw4r::math::VEC2 mPos;
        nw4r::math::VEC2 mScale;

        char mName[NAME_LENGTH + 1];
    };
}

#endif