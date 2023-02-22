#include "caddiePane.h"

#include <cstring>

namespace caddie {

Pane::Pane()
    : mIsUserAllocated(false),
      mParent(NULL),
      mIsVisible(true),
      mPosition(0.0f, 0.0f) {
    std::memset(mName, 0, sizeof(mName));
}

Pane::~Pane() {
    TLinkList<Pane>::Iterator it = mChildren.Begin();
    for (; it != mChildren.End(); it++) {
        TLinkList<Pane>::Iterator next = it++;

        // Remove from parent
        if (mParent != NULL) {
            mParent->RemoveChild(*this);
        }

        // Free heap memory if possible
        if (next->IsUserAllocated()) {
            mChildren.Remove(next);
            delete &*next;
        }
    }
}

/**
 * @brief Draw pane and all children (user-level)
 */
void Pane::UserDraw() const {
    UserDrawSelf();

    TLinkList<Pane>::Iterator it = mChildren.Begin();
    for (; it != mChildren.End(); it++) {
        it->UserDraw();
    }
}

/**
 * @brief Draw pane and all children (debug-level)
 */
void Pane::DebugDraw() const {
    DebugDrawSelf();

    TLinkList<Pane>::Iterator it = mChildren.Begin();
    for (; it != mChildren.End(); it++) {
        it->DebugDraw();
    }
}

/**
 * @brief Append child pane
 *
 * @param child Child pane
 */
void Pane::AppendChild(Pane& child) {
    mChildren.Append(&child);
    child.SetParent(this);
}

/**
 * @brief Remove child pane
 *
 * @param child Child pane
 */
void Pane::RemoveChild(const Pane& child) {
    // Look for child pane in list, by address
    TLinkList<Pane>::Iterator it = mChildren.Begin();
    for (; it != mChildren.End(); it++) {
        if (&*it == &child) {
            it->~Pane();
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
        if (std::strcmp(name, it->mName) == 0) {
            return &*it;
        }
    }

    return NULL;
}

/**
 * @brief Set pane position
 *
 * @param pos Position
 * @param type Method of solving position
 */
void Pane::SetPosition(Vec2<f32> pos, PositionType type) {
    // Relative to (0, 0) if no parent
    if (type == POS_TYPE_REL && mParent == NULL) {
        type = POS_TYPE_ABS;
    }

    switch (type) {
    case POS_TYPE_ABS:
        mPosition = pos;
        break;
    case POS_TYPE_REL:
        mPosition = mParent->GetPosition() + pos;
        break;
    }
}

/**
 * @brief Set pane name
 *
 * @param name New name
 */
void Pane::SetName(const char* name) {
    CADDIE_ASSERT(name != NULL);
    CADDIE_WARN_EX(std::strlen(name) > PANE_NAME_LEN,
                   "Pane name too long! (%s)", name);

    // Append null terminator
    std::strncpy(mName, name, PANE_NAME_LEN);
    mName[PANE_NAME_LEN + 1] = '\0';
}

} // namespace caddie
