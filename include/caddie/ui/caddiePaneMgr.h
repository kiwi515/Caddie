#ifndef CADDIE_UI_PANE_MGR_H
#define CADDIE_UI_PANE_MGR_H
#include "caddieLinkList.h"
#include "caddieStack.h"
#include "caddieVector.h"
#include "types_caddie.h"

namespace caddie {

/**
 * @brief Pane (UI) manager
 */
class PaneMgr {
public:
    static PaneMgr& GetInstance() {
        static PaneMgr instance;
        return instance;
    }

    //! Initialize
    virtual void Configure();
    //! Load resources
    virtual void LoadResource();
    //! Reset
    virtual void Reset();
    //! Update
    virtual void Calculate();
    //! User-level recursive draw
    virtual void UserDraw() const;
    //! Debug-level recursive draw
    virtual void DebugDraw() const;
    //! Terminate
    virtual void Exit();

    /**
     * @brief Push pane onto focus stack
     *
     * @param pane Pane
     */
    void Push(Pane& pane) { mPaneStack.Push(&pane); }

    /**
     * @brief Pop pane from focus stack
     *
     * @return Pane* Removed pane
     */
    void Pop() { Pane* old = mPaneStack.Pop(); }

private:
    PaneMgr();
    virtual ~PaneMgr();

private:
    //! @brief Pane focus stack
    TStack<Pane> mPaneStack;
};

} // namespace caddie

#endif
