#include "caddieMenuMgr.h"
#include "caddieAssert.h"

#include <nw4r/math/math_types.h>

#include <egg/core/eggController.h>

using namespace nw4r;
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

        if (!IsVisible()) {
            return;
        }

        // Page currently in focus
        const MenuPage* currPage = mPageStack.Peek();
        CADDIE_ASSERT(currPage != NULL);

        // Select option
        if (mBtnTrig & BTN_A) {
            currPage->GetOption(mCursor).OnClick();
        }
        // Close current page
        else if (mBtnTrig & BTN_B) {
            if (mPageStack.Size() > 1) {
                mPageStack.Pop();
            }
        }
        // Move cursor up
        else if (mBtnTrig & BTN_UP) {
            mCursor = MAX(mCursor - 1, 0);
        }
        // Move cursor down
        else if (mBtnTrig & BTN_DOWN) {
            mCursor = MIN(mCursor + 1, currPage->GetNumOptions() - 1);
        }
        // Increment option
        else if (mBtnTrig & BTN_RIGHT) {
            currPage->GetOption(mCursor).Increment();
        }
        // Decrement option
        else if (mBtnTrig & BTN_LEFT) {
            currPage->GetOption(mCursor).Decrement();
        }

        // Update cursor screen position
        const math::VEC2 optionPos = currPage->GetOption(mCursor).GetOptionPosition();
        const math::VEC2 cursorPos(optionPos.mCoords.x - sCursorOffset, optionPos.mCoords.y);
        mCursorText.SetPosition(cursorPos);
    }

    /**
     * @brief Draw focused page
     */
    void MenuMgr::Draw() const
    {
        if (!IsVisible()) {
            return;
        }

        // Draw page
        const MenuPage* page = mPageStack.Peek();
        CADDIE_ASSERT(page != NULL);
        page->Draw();

        // Draw cursor
        mCursorText.Draw();
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

        // Toggle visibility
        if (mBtnTrig & BTN_PLUS) {
            SetVisible(!mIsVisible);
        }
    }

    /**
     * @brief Cursor text string
     */
    const char* MenuMgr::sCursorStr = "==>";

    /**
     * @brief Cursor text color
     */
    const ut::Color MenuMgr::sCursorColor(255, 0, 0, 255);

    /**
     * @brief Cursor text X offset from option
     */
    const f32 MenuMgr::sCursorOffset = 35.0f;
}