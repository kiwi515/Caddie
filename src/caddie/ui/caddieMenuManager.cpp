// #include "caddieMenuManager.h"
// #include "caddieMenuOption.h"
// #include "caddieGolfMenu.h"
// #include "caddieAssert.h"

// #include "eggController.h"

// #include "ut_Color.h"

// #include <RPSysSceneCreator.h>

// #include <Sp2Util.h>
// #include <Sp2StaticMem.h>
// #include <Glf/Sp2GlfDefine.h>

// #define COLOR_UNSELECT 0xFFFFFFFF
// #define COLOR_CURSOR 0xFFFF0000
// #define COLOR_SHADOW 0xFF000000
// #define COLOR_DISABLED 0xFF8E8E8E

// #define OPTION_GAP_Y 20.0f
// #define OPTION_GAP_X 200.0f

// #define THIS_OPTION_HEIGHT (i * OPTION_GAP_Y)
// #define SELECTION_OPTION_HEIGHT (mSelection * OPTION_GAP_Y)

// #define OPTION_TIMER_FULL 15
// #define SETTING_TIMER_FULL OPTION_TIMER_FULL

// namespace caddie
// {
//     using namespace nw4r;
//     using namespace EGG;

//     void MenuManager::Open(MenuType type)
//     {
//         mSelection = 0;
//         mType = type;

//         switch(type)
//         {
//             case MENU_GOLF:
//                 mMenu = sGolfMenu;
//                 mMenuSize = GOLFMENU_MAX;
//                 break;
//             default:
//                 CADDIE_ASSERT_EX(false, "Attempted to open invalid menu\n");
//         }
//     }

//     void MenuManager::Draw(f32 baseX, f32 baseY)
//     {
//         if (!mIsVisible) return;

//         for (int i = 0; i < mMenuSize; i++)
//         {
//             // Print cursor
//             Sp2::PrintOutline("==>", COLOR_CURSOR, COLOR_SHADOW, false, baseX - 35.0f, baseY + SELECTION_OPTION_HEIGHT);

//             // Disabled options are printed in gray for readability
//             u32 color = (mMenu[i].IsEnabled()) ? COLOR_UNSELECT : COLOR_DISABLED;

//             // NULL name is the menu terminator
//             if (mMenu[i].GetName() == NULL)
//             {
//                 Sp2::PrintOutline("Save & Exit", COLOR_UNSELECT, COLOR_SHADOW, false, baseX, baseY + THIS_OPTION_HEIGHT);
//                 return;
//             }

//             // Option name
//             Sp2::PrintOutline(mMenu[i].GetName(), color, COLOR_SHADOW, false, baseX, baseY + THIS_OPTION_HEIGHT);

//             // Option setting
//             char buf[512];
//             mMenu[i].GetDataStr(buf);
//             Sp2::PrintOutline((mMenu[i].IsEnabled() ? buf : "DISABLED"), color, COLOR_SHADOW, false, baseX + OPTION_GAP_X, baseY + THIS_OPTION_HEIGHT);
//         }
//     }

//     void MenuManager::DoTick()
//     {
//         // Shouldn't be a problem because no one will wait (2^32 / 2) - 1 frames for the underflow but just to make sure
//         if (--mOptionTimer < 0) mOptionTimer = 0;
//         if (--mSettingTimer < 0) mSettingTimer = 0;
//     }

//     void MenuManager::Calc()
//     {
//         DoTick();
//         BuildInputHistory();

//         // Check P1 input
//         u16 input = CoreControllerMgr::getInstance()->getNthController(0)->getButtons();

//         // Minus button is for opening, and closing without saving
//         if (Pressed(BTN_MINUS) && !PressedLastFrame(BTN_MINUS)) Toggle();

//         // Even though this is not the drawing routine,
//         // we do not want to interact with a menu we cannot see
//         if (!mIsVisible) return;

//         // Check for save & exit
//         if (input & BTN_A)
//         {
//             if (mMenu[mSelection].GetName() == NULL)
//             {
//                 // Close the menu while we are at it
//                 Hide();

//                 Save();
//                 Exit();
//             }
//         }

//         // Option select cooldown
//         // NOTE: Cooldown is for holding the button
//         // Tap presses can be as fast as you want
//         if (mOptionTimer <= 0
//             || !PressedLastFrame(BTN_UP) && !PressedLastFrame(BTN_DOWN))
//         {
//             // Select option
//             if (input & BTN_UP)
//             {
//                 // Wrap around backwards
//                 if (--mSelection < 0) mSelection = mMenuSize - 1;
//                 mOptionTimer = OPTION_TIMER_FULL;
//             }
//             else if (input & BTN_DOWN)
//             {
//                 // Wrap around forwards
//                 if (++mSelection >= mMenuSize) mSelection = 0;
//                 mOptionTimer = OPTION_TIMER_FULL;
//             }
//         }

//         // Setting adjust cooldown
//         // NOTE: Cooldown is for holding the button
//         // Tap presses can be as fast as you want
//         if (mSettingTimer <= 0
//             || !PressedLastFrame(BTN_RIGHT) && !PressedLastFrame(BTN_LEFT))
//         {
//             if (mMenu[mSelection].IsEnabled())
//             {
//                 // Adjust settings
//                 if (input & BTN_RIGHT)
//                 {
//                     mMenu[mSelection]++;
//                     mSettingTimer = SETTING_TIMER_FULL;
//                 }
//                 else if (input & BTN_LEFT)
//                 {
//                     mMenu[mSelection]--;
//                     mSettingTimer = SETTING_TIMER_FULL;
//                 }
//             }
//         }
//     }

//     void MenuManager::BuildInputHistory()
//     {
//         mInputHistory[mInputHistoryIdx] = CoreControllerMgr::getInstance()->getNthController(0)->getButtons();
//         mInputHistoryIdx = (mInputHistoryIdx + 1) % INPUT_HISTORY_SIZE;
//     }

//     void MenuManager::Save()
//     {
//         switch (mType)
//         {
//             case MENU_GOLF:

//                 break;
//             default:
//                 CADDIE_ASSERT_EX(false, "Invalid menu type\n");
//         }
//     }

//     void MenuManager::Exit()
//     {
//         switch (mType)
//         {
//             case MENU_GOLF:

//         }
//     }
// }