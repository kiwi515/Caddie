#include "caddiePaneMgr.h"

#include "caddiePane.h"

#include <cstring>

namespace caddie {

PaneMgr::PaneMgr() {}

PaneMgr::~PaneMgr() {}

/**
 * @brief Initialize focused pane
 */
void PaneMgr::Configure() {
    if (!mPaneStack.IsEmpty()) {
        mPaneStack.Peek()->Configure();
    }
}

/**
 * @brief Load focused pane resources
 */
void PaneMgr::LoadResource() {
    if (!mPaneStack.IsEmpty()) {
        mPaneStack.Peek()->LoadResource();
    }
}

/**
 * @brief Reset focused pane
 */
void PaneMgr::Reset() {
    if (!mPaneStack.IsEmpty()) {
        mPaneStack.Peek()->Reset();
    }
}

/**
 * @brief Update focused pane
 */
void PaneMgr::Calculate() {
    if (!mPaneStack.IsEmpty()) {
        mPaneStack.Peek()->Calculate();
    }
}

/**
 * @brief Draw focused pane (user-level)
 */
void PaneMgr::UserDraw() const {
    if (!mPaneStack.IsEmpty()) {
        mPaneStack.Peek()->UserDraw();
    }
}

/**
 * @brief Draw focused pane (debug-level)
 */
void PaneMgr::DebugDraw() const {
#ifndef NDEBUG
    if (!mPaneStack.IsEmpty()) {
        mPaneStack.Peek()->DebugDraw();
    }
#endif
}

/**
 * @brief Exit focused pane
 */
void PaneMgr::Exit() {
    if (!mPaneStack.IsEmpty()) {
        mPaneStack.Peek()->Exit();
    }
}

} // namespace caddie
