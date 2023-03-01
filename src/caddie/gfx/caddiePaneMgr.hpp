#ifndef CADDIE_UI_PANE_MGR_H
#define CADDIE_UI_PANE_MGR_H
#include "caddiePane.hpp"
#include "caddieStack.hpp"
#include "caddieVector.hpp"
#include "types_caddie.hpp"

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

    virtual void Configure();
    virtual void LoadResource();
    virtual void Reset();
    virtual void Calculate();
    virtual void UserDraw() const;
    virtual void DebugDraw() const;
    virtual void Exit();

    /**
     * @brief Push pane onto focus stack
     *
     * @param pane Pane
     */
    void Push(Pane& pane) { mPaneStack.Push(&pane); }

    /**
     * @brief Pop pane from focus stack
     */
    void Pop() {
        Pane* top = mPaneStack.Pop();

        // Free memory if possible
        if (top != NULL && top->IsUserAllocated()) {
            delete top;
        }
    }

private:
    PaneMgr();
    virtual ~PaneMgr();

private:
    //! @brief Pane focus stack
    TStack<Pane> mPaneStack;
};

} // namespace caddie

#endif
