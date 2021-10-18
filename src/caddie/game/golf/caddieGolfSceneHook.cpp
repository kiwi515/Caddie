#include "caddieGolfSceneHook.h"

#include <Sp2Util.h>

#define COLOR_TIMER_TEXT 0xFFFFFFFF
#define COLOR_TIMER_OUTLINE 0xFF000000

#define GOLF_TIMER_X 650.0f
#define GOLF_TIMER_Y 30.0f

#define GOLF_TIMER_SCALE 1.5f

namespace caddie
{
    UNKTYPE * GolfSceneHook::OnInit(UNKTYPE *obj)
    {
        sIGTTimer.Start();

        return obj;
    }

    UNKTYPE * GolfSceneHook::OnFrame(UNKTYPE *obj)
    {
        sIGTTimer.Update();
        u32 frames = sIGTTimer.Elapsed();

        u32 seconds = frames / 60;
        frames %= 60;

        u32 minutes = seconds / 60;
        seconds %= 60;

        char buf[512];
        sprintf(buf, "IGT: %0.2d:%0.2d:%0.2d\n", minutes, seconds, frames);
        Sp2::PrintOutline(buf, COLOR_TIMER_TEXT, COLOR_TIMER_OUTLINE, false, GOLF_TIMER_X, GOLF_TIMER_Y, GOLF_TIMER_SCALE);

        return obj;
    }

    IGTTimer GolfSceneHook::sIGTTimer;
}