#include "caddiePane.h"

#include <cstring>

namespace caddie {

Pane::Pane() : mParent(NULL) {}

Pane::~Pane() {
    // TODO: Fix this

    // TLinkList<Pane>::Iterator it = mChildren.Begin();
    // for (; it != mChildren.End(); it++) {
    //     TLinkList<Pane>::Iterator next = it++;
    //     mChildren.Remove(next);
    //     delete &*next;
    // }
}

/**
 * @brief Draw pane and all children
 */
void Pane::Draw() const {
    DrawSelf();

    TLinkList<Pane>::Iterator it = mChildren.Begin();
    for (; it != mChildren.End(); it++) {
        it->Draw();
    }
}

/**
 * @brief Append child pane
 *
 * @param child Child pane
 */
void Pane::AppendChild(Pane* child) {
    CADDIE_ASSERT(child != NULL);

    mChildren.Append(child);
    child->SetParent(this);
}

/**
 * @brief Remove child pane
 *
 * @param child Child pane
 */
void Pane::RemoveChild(const Pane* child) {
    CADDIE_ASSERT(child != NULL);

    // Look for child pane in list, by address
    TLinkList<Pane>::Iterator it = mChildren.Begin();
    for (; it != mChildren.End(); it++) {
        if (&*it == child) {
            it->SetParent(NULL);
            mChildren.Remove(it);
        }
    }
}

/**
 * @brief Find child pane by name
 *
 * @param name Target pane name
 * @return Pane* Child pane
 */
Pane* Pane::FindChild(const char* name) const {
    CADDIE_ASSERT(name != NULL);

    TLinkList<Pane>::Iterator it = mChildren.Begin();
    for (; it != mChildren.End(); it++) {
        if (strcmp(name, it->mName) == 0) {
            return &*it;
        }
    }

    return NULL;
}

/**
 * @brief Set pane name
 *
 * @param name New name
 */
void Pane::SetName(const char* name) {
    CADDIE_ASSERT(name != NULL);

    // Warn if pane name will be truncated
    CADDIE_WARN_EX(strlen(name) > PANE_NAME_LEN, "Pane name too long! (%s)",
                   name);

    // Append null terminator
    strncpy(mName, name, PANE_NAME_LEN);
    mName[PANE_NAME_LEN + 1] = '\0';
}

} // namespace caddie
