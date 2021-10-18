#include "caddieMenuBase.h"
#include "caddieMenuOptionBase.h"
#include "caddieAssert.h"
#include "caddieDebug.h"

#include "eggController.h"

#include <Sp2Util.h>

#define COLOR_CURSOR 0xFFFF0000
#define COLOR_SHADOW 0xFF000000
#define COLOR_ENABLED 0xFFFFFFFF
#define COLOR_DISABLED 0xFF8E8E8E

#define OPTION_GAP_Y 20.0f
#define OPTION_GAP_X 200.0f

#define THIS_OPTION_HEIGHT (i * OPTION_GAP_Y)
#define SELECTION_OPTION_HEIGHT (mSelection * OPTION_GAP_Y)

#define OPTION_TIMER_FULL 15
#define SETTING_TIMER_FULL OPTION_TIMER_FULL

namespace caddie
{
    using namespace nw4r;
    using namespace EGG;

    MenuBase::~MenuBase()
    {
        MenuOptionBase *node = NULL;
        while (node = (MenuOptionBase *)ut::List_GetFirst(&mOptions))
        {
            delete node;
        }
    }

    void MenuBase::Calc()
    {
        DoTick();
        BuildHistory();

        // Menus replace the in-game pause functionality
        if (Pressed(BTN_PLUS) && !PressedLastFrame(BTN_PLUS)) Toggle();

        // Even though this is not the drawing routine,
        // we do not want to interact with a menu we cannot see
        if (!mIsVisible) return;

        // Check for save & exit
        if (Pressed(BTN_A))
        {
            MenuOptionBase *pSelection = (MenuOptionBase *)ut::List_GetNth(&mOptions, mSelection);
            CADDIE_ASSERT(pSelection != NULL);

            if (pSelection->OnConfirm()) Hide();
        }

        // Option select cooldown
        // NOTE: Cooldown is for holding the button
        // Tap presses can be as fast as you want
        if (mOptionTimer <= 0
            || !PressedLastFrame(BTN_UP) && !PressedLastFrame(BTN_DOWN))
        {
            // Select option
            if (Pressed(BTN_UP))
            {
                // Wrap around backwards
                if (--mSelection < 0) mSelection = GetNumOptions() - 1;
                mOptionTimer = OPTION_TIMER_FULL;
            }
            else if (Pressed(BTN_DOWN))
            {
                // Wrap around forwards
                if (++mSelection >= GetNumOptions()) mSelection = 0;
                mOptionTimer = OPTION_TIMER_FULL;
            }
        }

        // Setting adjust cooldown
        // NOTE: Cooldown is for holding the button
        // Tap presses can be as fast as you want
        if (mSettingTimer <= 0
            || !PressedLastFrame(BTN_RIGHT) && !PressedLastFrame(BTN_LEFT))
        {
            MenuOptionBase *pSelection = (MenuOptionBase *)ut::List_GetNth(&mOptions, mSelection);
            CADDIE_ASSERT(pSelection != NULL);

            if (pSelection->IsEnabled())
            {
                // Adjust settings
                if (Pressed(BTN_RIGHT))
                {
                    (*pSelection)++;
                    mSettingTimer = SETTING_TIMER_FULL;
                }
                else if (Pressed(BTN_LEFT))
                {
                    (*pSelection)--;
                    mSettingTimer = SETTING_TIMER_FULL;
                }
            }
        }
    }

    void MenuBase::Draw(f32 baseX, f32 baseY) const
    {
        if (!IsVisible()) return;

        MenuOptionBase *pOption = NULL;
        for (int i = 0; i < GetNumOptions(); i++)
        {
            pOption = (MenuOptionBase *)ut::List_GetNext(&mOptions, pOption);
            CADDIE_ASSERT(pOption != NULL);

            // Disabled options are printed in gray for readability
            pOption->Draw(baseX, baseY + THIS_OPTION_HEIGHT, OPTION_GAP_X, (pOption->IsEnabled()) ? COLOR_ENABLED : COLOR_DISABLED);
        }

        // Print cursor
        Sp2::PrintOutline("==>", COLOR_CURSOR, COLOR_SHADOW, false, baseX - 35.0f, baseY + SELECTION_OPTION_HEIGHT);
    }

    void MenuBase::DumpAll(f32 baseX, f32 baseY) const
    {
        MenuOptionBase *node = NULL;
        for (int i = 0; i < GetNumOptions(); i++)
        {
            node = (MenuOptionBase *)ut::List_GetNext(&mOptions, node);
            if (node == NULL) return;

            char buf[512];
            sprintf(buf, "Slot %d: %s (0x%08X)\n", i, node->GetName(), node);
            Sp2::PrintOutline(buf, COLOR_ENABLED, COLOR_SHADOW, false, baseX, baseY + THIS_OPTION_HEIGHT);
        }
    }

    void MenuBase::DoTick()
    {
        if (--mOptionTimer < 0) mOptionTimer = 0;
        if (--mSettingTimer < 0) mSettingTimer = 0;
    }

    void MenuBase::BuildHistory()
    {
        CoreControllerMgr *mgr = CoreControllerMgr::getInstance();
        CADDIE_ASSERT(mgr != NULL);

        mInputHistory[mInputHistoryIdx] = mgr->getNthController(0)->getButtons();
        mInputHistoryIdx = (mInputHistoryIdx + 1) % INPUT_HISTORY_SIZE;
    }
}