#ifndef CADDIE_SCENE_UI_TIMER_H
#define CADDIE_SCENE_UI_TIMER_H

#include <caddie/ui/caddieTextBox.h>

#include "types_caddie.h"

#include <nw4r/math.h>
#include <nw4r/ut.h>

namespace caddie {

    class Timer {
    public:
        Timer();
        ~Timer();

        void Start();
        void Stop();
        void Reset();

        void Freeze(u32 duration);

        virtual void Calc();
        virtual void Draw();

    private:
        bool mRunning;
        u32 mTimerValue;

        u32 mFrozenValue;
        u32 mFrozenDuration;

        TextBox mTextBox;

    // default timer position on screen
    static const nw4r::math::VEC2 sTimerPos;
    // default timer text colors
    static const nw4r::ut::Color sTimerRunningColor;
    static const nw4r::ut::Color sTimerFrozenColor;
    static const nw4r::ut::Color sTimerStoppedColor;
    };

}

#endif // CADDIE_SCENE_UI_TIMER_H