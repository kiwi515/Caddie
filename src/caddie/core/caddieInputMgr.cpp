#include "caddieInputMgr.h"

#include <egg/core.h>

namespace caddie {

/**
 * @brief Update player input
 */
void InputMgr::Calc() {
    for (int i = 0; i < PLAYER_MAX; i++) {
        const EGG::CoreController* cont =
            EGG::CoreControllerMgr::getInstance().getNthController(i);
        CADDIE_ASSERT(cont != NULL);

        // Buttons held last frame
        const u32 heldLastFrame = mBtnHeld[i];
        // Held buttons
        mBtnHeld[i] = cont->getButtons();
        // Buttons just pressed
        mBtnTrig[i] = mBtnHeld[i] & ~heldLastFrame;
        // Buttons released
        mBtnReleased[i] = heldLastFrame & ~mBtnHeld[i];
    }
}

} // namespace caddie
