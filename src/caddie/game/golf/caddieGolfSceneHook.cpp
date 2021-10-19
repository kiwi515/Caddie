#include "caddieGolfSceneHook.h"

#include <Sp2Util.h>

#define COLOR_TIMER_TEXT 0xFFFFFFFF
#define COLOR_TIMER_OUTLINE 0xFF000000

#define GOLF_TIMER_X 650.0f
#define GOLF_TIMER_Y 20.0f

#define GOLF_TIMER_SCALE 1.0f

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
        if (!*((bool *)0x80CFBAED))
        {
            sHoleOutIGT.Update();
        }

        u32 frames = sHoleOutIGT.Elapsed();

        u32 seconds = frames / 60;
        frames %= 60;

        u32 minutes = seconds / 60;
        seconds %= 60;

        char buf[512];
        sprintf(buf, "Hole Out (IGT): %0.2d:%0.2d:%0.2d\n", minutes, seconds, frames);
        Sp2::PrintOutline(buf, COLOR_TIMER_TEXT, COLOR_TIMER_OUTLINE, false, GOLF_TIMER_X, GOLF_TIMER_Y, GOLF_TIMER_SCALE);
    }

    IGTTimer GolfSceneHook::sHoleOutIGT;
}