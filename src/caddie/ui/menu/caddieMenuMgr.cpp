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
        CADDIE_ASSERT(mOpenPage != NULL);

        // Update player input
        CalcInput();

        if (!IsVisible()) {
            return;
        }

        // Select option
        if (mBtnTrig & BTN_A) {
            mOpenPage->GetOption(mCursor).OnClick();
        }
        // Close current page
        else if (mBtnTrig & BTN_B) {
            ClosePage();
        }
        // Move cursor up
        else if (mBtnTrig & BTN_UP) {
            mCursor = MAX(mCursor - 1, 0);
        }
        // Move cursor down
        else if (mBtnTrig & BTN_DOWN) {
            mCursor = MIN(mCursor + 1, mOpenPage->GetNumOptions() - 1);
        }
        // Increment option
        else if (mBtnTrig & BTN_RIGHT) {
            mOpenPage->GetOption(mCursor).Increment();
        }
        // Decrement option
        else if (mBtnTrig & BTN_LEFT) {
            mOpenPage->GetOption(mCursor).Decrement();
        }

        // Update cursor screen position
        const math::VEC2 optionPos = mOpenPage->GetOption(mCursor).GetOptionPosition();
        const math::VEC2 cursorPos(optionPos.mCoords.x - sCursorOffset, optionPos.mCoords.y);
        mCursorText.SetPosition(cursorPos);
    }

    /**
     * @brief Draw focused page
     */
    void MenuMgr::Draw() const
    {
        CADDIE_ASSERT(mOpenPage != NULL);

        if (!IsVisible()) {
            return;
        }

        // Draw page
        mOpenPage->Draw();
        // Draw cursor
        mCursorText.Draw();
    }

    /**
     * @brief Update P1 input
     */
    void MenuMgr::CalcInput()
    {
        CADDIE_ASSERT(mOpenPage != NULL);

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
            
            // Delete changes on menu close
            if (!IsVisible()) {
                mOpenPage->DeleteChanges();
            }
        }
    }

    //! @brief Cursor text string
    const char* MenuMgr::sCursorStr = "==>";
    //! @brief Cursor text color
    const ut::Color MenuMgr::sCursorColor(255, 0, 0, 255);
    //! @brief Cursor text X offset from option
    const f32 MenuMgr::sCursorOffset = 35.0f;
}