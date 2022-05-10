#include "caddiePane.h"
#include "caddieAssert.h"
#include <string.h>

namespace caddie
{
    Pane::Pane() :
        mParent(NULL)
    {
    }

    Pane::~Pane()
    {
        PaneIterator it = mChildren.Begin();
        for (; it != mChildren.End(); it++) {
            delete &*it;
        }
    }

    /**
     * @brief Draw pane and all children
     */
    void Pane::Draw() const
    {
        DrawSelf();
        
        PaneIterator it = mChildren.Begin();
        for (; it != mChildren.End(); it++) {
            it->Draw();
        }
    }

    /**
     * @brief Find child pane by name
     * 
     * @param name Target pane name
     * @return Pane* Child pane
     */
    Pane* Pane::FindChild(const char* name) const
    {
        CADDIE_ASSERT(name != NULL);

        PaneIterator it = mChildren.Begin();
        for (; it != mChildren.End(); it++) {
            if (strcmp(name, it->mName) == 0) {
                return &*it;
            }
        }

        return NULL;
    }

    /**
     * @brief Append child pane
     * 
     * @param child Child pane
     */
    void Pane::AppendChild(Pane* child)
    {
        CADDIE_ASSERT(child != NULL);

        mChildren.Append(child);
        child->SetParent(this);
    }

    /**
     * @brief Remove child pane
     * 
     * @param child Child pane
     */
    void Pane::RemoveChild(const Pane* child)
    {
        CADDIE_ASSERT(child != NULL);

        // Look for child pane in list, by address
        PaneIterator it = mChildren.Begin();
        for (; it != mChildren.End(); it++) {
            if (&*it == child) {
                it->SetParent(NULL);
                mChildren.Remove(it);
            }
        }
    }

    /**
     * @brief Set pane name
     * 
     * @param name New name
     */
    void Pane::SetName(const char* name)
    {
        CADDIE_ASSERT(name != NULL);

        // Warn if pane name will be truncated
        const size_t len = strlen(name);
        if (len > PANE_NAME_LEN) {
            CADDIE_LOG("Pane name too long! (%s)", name);
        }

        // Append null terminator
        strncpy(mName, name, PANE_NAME_LEN);
        mName[PANE_NAME_LEN + 1] = '\0';
    }
}