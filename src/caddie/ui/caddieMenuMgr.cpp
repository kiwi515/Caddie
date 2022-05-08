#include "caddieMenuMgr.h"
#include "caddieAssert.h"
#include <egg/core/eggController.h>

using namespace EGG;

namespace caddie
{
    /**
     * @brief Menu logic
     */
    void MenuMgr::Calc()
    {
        // Update player input
        CalcInput();

        // Page currently in focus
        const MenuPage* currPage = mPageStack.Peek();
        CADDIE_ASSERT(currPage != NULL);

        // Select option
        if (mBtnTrig & BTN_A) {
            IMenuOption *opt = currPage->GetOption(mCursor);
            CADDIE_ASSERT(opt != NULL);
            opt->OnClick();
        }
        // Close current page
        else if (mBtnTrig & BTN_B) {
            mPageStack.Pop();
        }
        // Move cursor up
        else if (mBtnHeld & BTN_UP) {
            mCursor = MAX(mCursor - 1, 0);
        }
        // Move cursor down
        else if (mBtnHeld & BTN_DOWN) {
            mCursor = MIN(mCursor + 1, currPage->GetNumOptions());
        }
    }

    /**
     * @brief Draw focused page
     */
    void MenuMgr::Draw() const
    {
        mPageStack.Peek()->Draw();
    }

    /**
     * @brief Update P1 input
     */
    void MenuMgr::CalcInput()
    {
        // Update player input
        CoreControllerMgr* contMgr = CoreControllerMgr::getInstance();
        CADDIE_ASSERT(contMgr != NULL);
        // Only use player 1 input
        CoreController* cont = contMgr->getNthController(0);
        CADDIE_ASSERT(cont != NULL);

        // Buttons held last frame
        const u32 heldLastFrame = mBtnHeld;
        // Held buttons
        mBtnHeld = cont->getButtons();
        // Buttons just pressed
        mBtnTrig = mBtnHeld & ~heldLastFrame;
        // Buttons released
        mBtnReleased = heldLastFrame & ~mBtnHeld;
    }
}