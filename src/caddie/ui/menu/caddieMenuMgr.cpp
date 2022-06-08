#include "caddieMenuMgr.h"

#include "caddieAssert.h"
#include "caddieInputMgr.h"

#include <egg/core/eggController.h>
#include <nw4r/math/math_types.h>

using namespace nw4r;
using namespace EGG;

namespace caddie {

/**
 * @brief Menu logic
 */
void MenuMgr::Calc() {
    CalcInput();

    // All players can control the menu
    for (int i = 0; i < InputMgr::PLAYER_MAX; i++) {
        // Read from input mgr
        const InputMgr::EPlayer player = (InputMgr::EPlayer)i;
        const u32 trig = InputMgr::GetInstance().Trig(player);
        const u32 held = InputMgr::GetInstance().Held(player);

        // Toggle visibility
        if (trig & BTN_PLUS) {
            SetVisible(!mIsVisible);

            // Delete changes on menu close
            if (!IsVisible() && mOpenPage != NULL) {
                mOpenPage->DeleteChanges();
            }
        }

        if (!IsVisible() || mMenu == NULL || mOpenPage == NULL) {
            return;
        }

        // Select option
        if (trig & BTN_A) {
            mOpenPage->GetOption(mCursor).OnClick();
        }
        // Close current page
        else if (trig & BTN_B) {
            ClosePage();
        }

        // Initial up input before DAS
        if ((trig & BTN_UP && mControlDAS[i] == sControlMaxDAS) ||
            // Auto repeat up
            (held & BTN_UP && mControlARR[i] <= 0)) {
            // Wrap around
            if (--mCursor < 0) {
                mCursor = mOpenPage->GetNumOptions() - 1;
            }
        }
        // Initial down input before DAS
        else if ((trig & BTN_DOWN && mControlDAS[i] == sControlMaxDAS) ||
                 // Auto repeat down
                 (held & BTN_DOWN && mControlARR[i] <= 0)) {
            // Wrap around
            if (++mCursor >= mOpenPage->GetNumOptions()) {
                mCursor = 0;
            }
        }
        // Initial right input before DAS
        else if ((trig & BTN_RIGHT && mControlDAS[i] == sControlMaxDAS) ||
                 // Auto repeat right
                 (held & BTN_RIGHT && mControlARR[i] <= 0)) {
            mOpenPage->GetOption(mCursor).Increment();
            mMenu->OnChange();
        }
        // Initial left input before DAS
        else if ((trig & BTN_LEFT && mControlDAS[i] == sControlMaxDAS) ||
                 // Auto repeat left
                 (held & BTN_LEFT && mControlARR[i] <= 0)) {
            mOpenPage->GetOption(mCursor).Decrement();
            mMenu->OnChange();
        }
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
    if (!IsVisible() || mMenu == NULL || mOpenPage == NULL) {
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
    for (int i = 0; i < InputMgr::PLAYER_MAX; i++) {
        const InputMgr::EPlayer player = (InputMgr::EPlayer)i;
        const u32 trig = InputMgr::GetInstance().Trig(player);

        // Reset DAS/ARR on D-Pad input change
        if (trig & BTN_DPAD_ALL) {
            mControlDAS[i] = sControlMaxDAS;
            mControlARR[i] = sControlMaxARR;
        } else {
            mControlDAS[i] = Max<s32>(mControlDAS[i] - 1, 0);
        }

        // Auto repeat after DAS ends
        if (mControlDAS[i] <= 0) {
            mControlARR[i]--;
            if (mControlARR[i] < 0) {
                mControlARR[i] = sControlMaxARR;
            }
        }
    }
}

const u32 MenuMgr::sControlMaxDAS = 15;
const u32 MenuMgr::sControlMaxARR = 8;

const char* MenuMgr::sCursorStr = "==>";
const ut::Color MenuMgr::sCursorColor(255, 0, 0, 255);
const f32 MenuMgr::sCursorOffset = 35.0f;

} // namespace caddie
