#include "caddie/ui/timer/caddieTimer.h"
#include "caddie/ui/caddieTextBox.h"

#include <cstdio>
#include <cstring>

#include <nw4r/math.h>

namespace caddie {

Timer::Timer()
    : mRunning(false),
      mTimerValue(0),
      mFrozenValue(0),
      mFrozenDuration(0),
      mTextBox() {
          mTextBox.SetText("0.00");
          mTextBox.SetPosition(sTimerPos);
          mTextBox.SetStroke(TextBox::STROKE_OUTLINE);
      }

const nw4r::math::VEC2 Timer::sTimerPos(8.0f, 20.0f);

const nw4r::ut::Color Timer::sTimerRunningColor(0, 255, 255, 255);
const nw4r::ut::Color Timer::sTimerFrozenColor(0, 180, 180, 255);
const nw4r::ut::Color Timer::sTimerStoppedColor(180, 180, 180, 255);


Timer::~Timer() {}

void Timer::Start() {
    mRunning = true;
}

void Timer::Stop() {
    mRunning = false;
}

void Timer::Reset() {
    mTimerValue = 0;
    mFrozenValue = 0;
    mFrozenDuration = 0;
}

void Timer::Freeze(u32 duration) {
    mFrozenValue = mTimerValue;
    mFrozenDuration = duration;
}

void Timer::Calc() {

    if (mRunning) {
        ++mTimerValue;
        
        if (mFrozenDuration > 0) {
            --mFrozenDuration;
        }
    }

    // decide color
    nw4r::ut::Color color;
    if (mRunning) {
        if (mFrozenDuration > 0) {
            color = sTimerFrozenColor;
        }
        else {
            color = sTimerRunningColor;
        }
    } else {
        color = sTimerStoppedColor;
    }
    mTextBox.SetTextColor(color);

    u32 valueToDisplay = mFrozenDuration > 0 ? mFrozenValue : mTimerValue;
    mTextBox.SetTextFmt("%.2f", valueToDisplay / 60.0f);
}

void Timer::Draw() {
    mTextBox.Draw();
}

}