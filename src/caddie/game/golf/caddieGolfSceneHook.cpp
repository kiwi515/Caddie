#include "caddieGolfSceneHook.h"
#include "caddieGolfMenu.h"
#include "caddieMenuEnumOption.h"
#include "caddieGolfMisc.h"

#include <Glf/Sp2GlfMain.h>
#include <Glf/Sp2GlfBallMgr.h>
#include <Sp2Util.h>

#include <core/eggController.h>

// Timer defs
#define COLOR_TIMER_TEXT 0xFFFFFFFF
#define COLOR_TIMER_OUTLINE 0xFF000000
#define GOLF_TIMER_X 650.0f
#define GOLF_TIMER_Y 20.0f
#define GOLF_TIMER_SCALE 1.0f

// Menu defs
#define GOLF_MENU_X 100.0f
#define GOLF_MENU_Y 200.0f

namespace caddie
{
    using namespace Sp2;
    using namespace EGG;

    void GolfSceneHook::OnInit()
    {

    }

    void GolfSceneHook::OnFrame()
    {
        GolfMenu *menu = GolfMenu::GetInstance();
        CADDIE_ASSERT(menu != NULL);

        menu->Calc();
        menu->Draw(GOLF_MENU_X, GOLF_MENU_Y);

        // CoreControllerMgr *mgr = CoreControllerMgr::getInstance();
        // CADDIE_ASSERT(mgr != NULL);
        // u16 input = mgr->getNthController(0)->getButtons();
        // // Stop the ball with (B + MINUS + 2)
        // if ((input & BTN_B) && (input & BTN_MINUS) && (input & BTN_2))
        // {
        //     Glf::GlfBallMgr::GetBall(0)->SetLifetime(0xCADD1E);
        // }
    }

    void GolfSceneHook::OnExit()
    {

    }

    void GolfSceneHook::OnUpdateHole()
    {
        GolfMenu *menu = GolfMenu::GetInstance();
        CADDIE_ASSERT(menu != NULL);

        menu->Validate();
        RepeatHoleIL();
    }
#ifdef CADDIE_REGION_NTSC_U
    kmBranch(0x80406a5c, &GolfSceneHook::OnUpdateHole);
#elif CADDIE_REGION_PAL
    kmBranch(0x80406d7c, &GolfSceneHook::OnUpdateHole);
#endif

}