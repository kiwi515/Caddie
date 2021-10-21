#include "caddieGolfSceneHook.h"
#include "caddieGolfMenu.h"
#include "caddieMenuEnumOption.h"
#include "caddieGolfMisc.h"

#include <Sp2GlfMain.h>
#include <Sp2Util.h>

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

    void GolfSceneHook::OnInit()
    {

    }

    void GolfSceneHook::OnFrame()
    {
        GolfMenu *menu = GolfMenu::GetInstance();
        CADDIE_ASSERT(menu != NULL);

        menu->Calc();
        menu->Draw(GOLF_MENU_X, GOLF_MENU_Y);
    }

    void GolfSceneHook::OnUpdateHole()
    {
        RepeatHoleIL();
    }
    kmBranch(0x80406a5c, &GolfSceneHook::OnUpdateHole);
}