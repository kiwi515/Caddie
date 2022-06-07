#include "caddieMenuMgr.h"

#include "caddieAssert.h"

#include <egg/core/eggController.h>
#include <nw4r/math/math_types.h>

using namespace nw4r;
using namespace EGG;

namespace caddie {

/**
 * @brief Menu logic
 */
void MenuMgr::Calc() {
    CADDIE_ASSERT(mMenu != NULL);
    CADDIE_ASSERT(mOpenPage != NULL);

    CalcInput();

    // Toggle visibility
    if (mBtnTrig & BTN_PLUS) {
        SetVisible(!mIsVisible);

        // Delete changes on menu close
        if (!IsVisible()) {
            mOpenPage->DeleteChanges();
        }
    }

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

    // Initial up input before DAS
    if ((mBtnTrig & BTN_UP && mControlDAS == sControlMaxDAS) ||
        // Auto repeat up
        ((mBtnHeld & BTN_UP) && mControlARR <= 0)) {
        mCursor--;
        // Wrap around
        if (mCursor < 0) {
            mCursor = mOpenPage->GetNumOptions() - 1;
        }
    }
    // Initial down input before DAS
    else if ((mBtnTrig & BTN_DOWN && mControlDAS == sControlMaxDAS) ||
             // Auto repeat down
             ((mBtnHeld & BTN_DOWN) && mControlARR <= 0)) {
        mCursor++;
        // Wrap around
        if (mCursor >= mOpenPage->GetNumOptions()) {
            mCursor = 0;
        }
    }
    // Initial right input before DAS
    else if ((mBtnTrig & BTN_RIGHT && mControlDAS == sControlMaxDAS) ||
             // Auto repeat right
             ((mBtnHeld & BTN_RIGHT) && mControlARR <= 0)) {
        mOpenPage->GetOption(mCursor).Increment();
        mMenu->OnChange();
    }
    // Initial left input before DAS
    else if ((mBtnTrig & BTN_LEFT && mControlDAS == sControlMaxDAS) ||
             // Auto repeat left
             ((mBtnHeld & BTN_LEFT) && mControlARR <= 0)) {
        mOpenPage->GetOption(mCursor).Decrement();
        mMenu->OnChange();
    }

    // Update cursor screen position
    const math::VEC2 optionPos =
        mOpenPage->GetOption(mCursor).GetOptionPosition();
    const math::VEC2 cursorPos(optionPos.mCoords.x - sCursorOffset,
                               optionPos.mCoords.y);
    mCursorText.SetPosition(cursorPos);
}

/**
 * @brief Draw focused page
 */
void MenuMgr::Draw() const {
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
void MenuMgr::CalcInput() {
    CADDIE_ASSERT(mOpenPage != NULL);

    // Update player input
    // (Only use player 1 input)
    const CoreController* cont =
        CoreControllerMgr::getInstance().getNthController(0);
    CADDIE_ASSERT(cont != NULL);

    // Buttons held last frame
    const u32 heldLastFrame = mBtnHeld;
    // Held buttons
    mBtnHeld = cont->getButtons();
    // Buttons just pressed
    mBtnTrig = mBtnHeld & ~heldLastFrame;
    // Buttons released
    mBtnReleased = heldLastFrame & ~mBtnHeld;

    // Reset DAS on D-Pad input change
    if (mBtnTrig & BTN_DPAD_ALL) {
        mControlDAS = sControlMaxDAS;
        mControlARR = sControlMaxARR;
    } else {
        mControlDAS = Max<s32>(mControlDAS - 1, 0);
    }

    // Auto repeat
    if (mControlDAS <= 0) {
        mControlARR--;
        if (mControlARR < 0) {
            mControlARR = sControlMaxARR;
        }
    }
}

const u32 MenuMgr::sControlMaxDAS = 15;
const u32 MenuMgr::sControlMaxARR = 8;

const char* MenuMgr::sCursorStr = "==>";
const ut::Color MenuMgr::sCursorColor(255, 0, 0, 255);
const f32 MenuMgr::sCursorOffset = 35.0f;

} // namespace caddie
