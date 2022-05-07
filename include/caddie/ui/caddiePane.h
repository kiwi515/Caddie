#ifndef CADDIE_UI_PANE_H
#define CADDIE_UI_PANE_H
#include "types_caddie.h"
#include "caddieTLinkList.h"
#include "caddieAssert.h"
#include "math_types.h"
#include <string.h>

namespace caddie
{
    /**
     * @brief Base UI class
     */
    class Pane
    {
    public:
        Pane();
        virtual ~Pane();
        virtual void Draw() const;
        virtual void DrawSelf() const = 0;
        virtual Pane* FindChild(const char* name) const;

        void AppendChild(Pane& child);
        void RemoveChild(const Pane* child);

        Pane* GetParent() const { return mParent; }
        void SetParent(Pane* p) { mParent = p; }

        nw4r::math::VEC2 GetPosition() const { return mPos; }
        void SetPosition(const nw4r::math::VEC2& pos) { mPos = pos; }

        f32 GetScale() const { return mScale; }
        void SetScale(f32 scale) { mScale = scale; }

        void SetName(const char *str);

    public:
        //! @brief Node for intrusive list
        TLinkListNode mNode;
        typedef TLinkList<Pane, offsetof(Pane, mNode)> PaneList;
        typedef PaneList::Iterator PaneIterator;

    protected:
        //! @brief Pane name max length
        static const int PANE_NAME_LEN = 16;

        //! @brief Parent pane
        Pane* mParent;
        //! @brief List of children
        PaneList mChildren;

        //! @brief Screenspace position
        nw4r::math::VEC2 mPos;
        //! @brief Scale
        f32 mScale;

        //! @brief Pane name
        char mName[PANE_NAME_LEN + 1];
    };
}

#endif