#include "caddieGolfSceneHook.h"
#include "caddieGolfMenu.h"

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
    void GolfSceneHook::OnInit()
    {
        sHoleOutIGT.Start();
        // The scene fader takes 2 frames to start fading in
        // Since timing begins on the first visible fade in frame,
        // we offset the timer by -2 frames
        sHoleOutIGT.SetElapsed(-2);
    }

    void GolfSceneHook::OnFrame()
    {
        GolfMenu *menu = GolfMenu::GetInstance();
        CADDIE_ASSERT(menu != NULL);

        menu->Calc();
        menu->Draw(GOLF_MENU_X, GOLF_MENU_Y);
    }

    IGTTimer GolfSceneHook::sHoleOutIGT;
}